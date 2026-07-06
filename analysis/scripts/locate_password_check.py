#!/usr/bin/env python3
"""
locate_password_check.py  --  pinpoint the BIOS unlock / master-password
verification module inside an extracted Dell UEFI image.

Background (the "black box"):
    The setup/unlock prompt takes a 16-char password, hands it to an SMM
    handler (SMI), and compares it against the first 16 bytes of a 32-byte
    SHA-256 digest computed over:

            SHA256( <serviceTag:7 chars>  <familyTag:4 chars> )

    i.e.  truncate16( SHA256(serviceTag || familyTag) ) == userInput.

    So the module we want is the one that (a) implements/uses SHA-256 and
    (b) carries one of the platform family tags and/or reads the service
    tag, and (c) does a 16-byte compare. This scanner ranks candidate PE
    modules by how many of those fingerprints they contain.

Usage:
    # scan a directory of extracted PE images (firmware/extracted/pe_images/<run>/)
    ./locate_password_check.py --scan firmware/extracted/pe_images/SystemBIOS_1.19.1/

    # or scan a raw firmware .bin / a single module directly
    ./locate_password_check.py --scan firmware/input/SystemBIOS_1.19.1.bin

    # add / override the candidate family tags to hunt for (comma separated)
    ./locate_password_check.py --scan <path> --tags 1F66,6FF1,1D3B,2A7B,BF97

    # inventory PE modules straight from a UEFIExtract report (no bytes needed)
    ./locate_password_check.py --from-report firmware/extracted/uefi/*.report.txt

Nothing here is Dell/family-tag specific by necessity: the SHA-256 constant
tables are a hard fingerprint that will flag every module doing SHA-256, and
the family tags / service-tag strings then disambiguate which of those is the
password check. Confirm the winner in Ghidra (see analysis/notes/).
"""

import argparse
import os
import struct
import sys

# ---------------------------------------------------------------------------
# Fingerprint 1: SHA-256 constant tables (present in any SHA-256 implementation)
# ---------------------------------------------------------------------------
# Initial hash values H0..H7
SHA256_H = [0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
            0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19]
# Round constants K0..K7 (first 8 of 64 is more than enough to be unique)
SHA256_K = [0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
            0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5]


def _const_needles(words):
    """Both byte orders, so we catch LE data tables and BE immediates."""
    le = b"".join(struct.pack("<I", w) for w in words)
    be = b"".join(struct.pack(">I", w) for w in words)
    return [("LE", le), ("BE", be)]


SHA256_NEEDLES = _const_needles(SHA256_H) + _const_needles(SHA256_K)

# ---------------------------------------------------------------------------
# Fingerprint 2: candidate platform family tags ("one of 5 in the family").
# These are the commonly-cited Dell suffix families; the *real* set for this
# platform must be confirmed against the binary -- override with --tags.
# ---------------------------------------------------------------------------
DEFAULT_TAGS = ["1F66", "6FF1", "1D3B", "2A7B", "BF97",
                "595B", "A95B", "1F5A", "E7A8", "D35B"]

# ---------------------------------------------------------------------------
# Fingerprint 3: service-tag / SMBIOS references (the 7-char unique id source)
# ---------------------------------------------------------------------------
SVCTAG_STRINGS = ["Service Tag", "ServiceTag", "SvcTag", "Service_Tag",
                  "Serial Number", "Asset Tag"]


def _ascii_and_utf16(s):
    """UEFI strings are frequently UTF-16LE; match both encodings."""
    return [s.encode("ascii"), s.encode("utf-16-le")]


def scan_blob(data, tags):
    """Return a dict of fingerprint hits for one blob of bytes."""
    hits = {"sha256": [], "tags": [], "svctag": []}

    for order, needle in SHA256_NEEDLES:
        if needle in data:
            hits["sha256"].append(order)

    for tag in tags:
        for enc in _ascii_and_utf16(tag):
            if enc in data:
                hits["tags"].append(tag)
                break

    for s in SVCTAG_STRINGS:
        for enc in _ascii_and_utf16(s):
            if enc in data:
                hits["svctag"].append(s)
                break

    return hits


def score(hits):
    """SHA-256 is the strongest signal; tags/service-tag confirm."""
    s = 0
    s += 10 if hits["sha256"] else 0
    s += 5 * len(set(hits["tags"]))
    s += 3 * len(set(hits["svctag"]))
    return s


def iter_files(path):
    if os.path.isfile(path):
        yield path
        return
    for root, _, files in os.walk(path):
        for f in sorted(files):
            yield os.path.join(root, f)


def cmd_scan(args):
    tags = [t.strip().upper() for t in args.tags.split(",")] if args.tags else DEFAULT_TAGS
    results = []
    for fp in iter_files(args.scan):
        try:
            with open(fp, "rb") as fh:
                data = fh.read()
        except (OSError, IOError):
            continue
        hits = scan_blob(data, tags)
        sc = score(hits)
        if sc > 0:
            results.append((sc, fp, hits))

    if not results:
        print("[!] No SHA-256 / family-tag / service-tag fingerprints found.")
        print("    If you scanned a compressed image, extract PE modules first")
        print("    (the extract_pipeline.sh Stage-2 dump), then scan that dir.")
        return 1

    results.sort(key=lambda r: r[0], reverse=True)
    print(f"[+] {len(results)} candidate module(s), best first:\n")
    for sc, fp, hits in results:
        print(f"  score={sc:<3}  {fp}")
        if hits["sha256"]:
            print(f"            SHA-256 const table   : {', '.join(hits['sha256'])}")
        if hits["tags"]:
            print(f"            family tag string(s)  : {', '.join(sorted(set(hits['tags'])))}")
        if hits["svctag"]:
            print(f"            service-tag string(s) : {', '.join(sorted(set(hits['svctag'])))}")
        print()

    top = results[0]
    print("-" * 60)
    print(f"[*] Prime suspect: {top[1]}  (score {top[0]})")
    print("    Next: load it in Ghidra, find the SHA-256 routine's caller,")
    print("    and look for a 16-byte CompareMem/memcmp against setup input.")
    return 0


def cmd_from_report(args):
    """List PE modules (GUID + offset) from a UEFIExtract report -- no bytes."""
    wanted = ("DXE driver", "SMM module", "PEI module")
    n = 0
    with open(args.from_report, "r", errors="replace") as fh:
        lines = fh.readlines()
    print("[*] PE-bearing modules in report (GUID | type | size):\n")
    for i, line in enumerate(lines):
        if "| File " not in line and not any(f"| {w} " in line for w in wanted):
            continue
        if not any(f"| {w} " in line for w in wanted):
            continue
        parts = [p.strip() for p in line.split("|")]
        # last column is "------ <GUID> [| name]"; strip the tree prefix
        guid = parts[-1].lstrip("- ").split()[0] if parts and parts[-1] else "?"
        typ = next((w for w in wanted if f"| {w} " in line), "?")
        size = parts[3] if len(parts) > 3 else "?"
        print(f"  {guid:<40} {typ:<11} {size}")
        n += 1
    print(f"\n[+] {n} PE modules. Regenerate the Stage-2 dump and --scan it to")
    print("    fingerprint which of these performs the SHA-256 password check.")
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--scan", metavar="PATH",
                   help="directory of PE images, or a single .bin/module to scan")
    g.add_argument("--from-report", metavar="REPORT",
                   help="UEFIExtract .report.txt to inventory PE modules from")
    ap.add_argument("--tags", metavar="T1,T2,...",
                    help="override candidate family tags (default: common Dell set)")
    args = ap.parse_args()

    if args.scan:
        return cmd_scan(args)
    return cmd_from_report(args)


if __name__ == "__main__":
    try:
        sys.exit(main())
    except BrokenPipeError:
        # allow clean piping into head/less without a traceback
        try:
            sys.stdout.close()
        finally:
            os.dup2(os.open(os.devnull, os.O_WRONLY), sys.stdout.fileno())
        sys.exit(0)
