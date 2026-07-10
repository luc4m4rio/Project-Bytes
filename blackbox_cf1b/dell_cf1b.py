"""Dell service-tag BIOS master-password generator (CLI).

Recovers the 16-char BIOS master password for a locked Dell service-tag prompt of
the form  TAG-SUFFIX  (submitted at the prompt with Ctrl+Enter). Intended for
owners recovering access to their own hardware.

- The 10 documented suffixes (595B, D35B, 2A7B, A95B, 1D3B, 1F66, 6FF1, 1F5A,
  BF97, E7A8) are generated directly and are byte-exact against published vectors.
- CF1B is UNDOCUMENTED and computed inside the machine's embedded controller
  (AES-encrypted firmware, no binary to reverse). It can only be recovered by
  fitting confirmed (tag -> password) pairs. Until enough data pins the algorithm,
  this tool refuses to emit an unverified CF1B password (see reverse_fit.py).

Usage:
    python3 dell_cf1b.py 1234567-1F5A
    python3 dell_cf1b.py JY5M453-CF1B
    python3 dell_cf1b.py --list
"""
from __future__ import annotations
import argparse
import os
import sys

import reference_dell as R
import reverse_fit

SOLVABLE = ("595B", "D35B", "2A7B", "A95B", "1D3B", "1F66",
            "6FF1", "1F5A", "BF97", "E7A8")

PAIRS_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "cf1b_pairs.json")


def parse_system_number(sysno):
    sysno = sysno.strip().upper()
    if "-" in sysno:
        tag, suffix = sysno.split("-", 1)
    else:
        tag, suffix = sysno[:7], sysno[7:]
    if len(tag) != 7 or len(suffix) != 4:
        raise ValueError(f"expected a 7-char tag and 4-char suffix, got {sysno!r}")
    return tag, suffix


def generate(sysno):
    """Return (list_of_passwords, note). Raises ValueError on malformed input."""
    tag, suffix = parse_system_number(sysno)

    if suffix in SOLVABLE:
        pws = R.keygen_dell(tag, suffix, hdd=False)
        return pws, None

    if suffix == "CF1B":
        return _generate_cf1b(tag)

    raise ValueError(f"unknown suffix {suffix!r}; solvable: {', '.join(SOLVABLE)}, "
                     f"plus CF1B (experimental)")


def _generate_cf1b(tag):
    pairs = reverse_fit.load_pairs(PAIRS_FILE)
    res = reverse_fit.best_fit(pairs)
    if not res["solved"]:
        note = (
            "CF1B is UNSOLVED from the current data.\n"
            f"  known confirmed pairs : {res['n_pairs']}\n"
            f"  best consistent fit   : {res['ceiling']} collisions "
            f"(need >= {res['threshold']}; this is indistinguishable from noise)\n"
            "  why                   : CF1B runs inside the EC (AES-encrypted firmware,\n"
            "                          no binary to reverse) and is a bespoke encoder,\n"
            "                          not a variant of any documented suffix.\n"
            "  to make progress      : add more confirmed tag->password pairs to\n"
            "                          cf1b_pairs.json and re-run; this tool will fit\n"
            "                          and generate automatically once the data suffices."
        )
        return [], note

    # Solved: only standard-hash hypotheses can generate directly.
    best = res["best"]
    if best["kind"] != "hash":
        return [], ("CF1B fit found via the block-encoder path; direct generation for "
                    "that path is not wired up (its output table is only partially "
                    "recovered). Re-run reverse_fit.py for details.")
    pw, unknown = reverse_fit.generate_standard(best, tag + "-CF1B")
    if unknown:
        note = (f"partial: positions {unknown} use table entries not yet seen in the "
                f"known pairs (shown as '?'). Add pairs covering them.")
        return [pw], note
    return [pw], None


def main(argv=None):
    ap = argparse.ArgumentParser(description="Dell service-tag BIOS master-password generator")
    ap.add_argument("system_number", nargs="?", help="e.g. 1234567-1F5A or JY5M453-CF1B")
    ap.add_argument("--list", action="store_true", help="list supported suffixes")
    args = ap.parse_args(argv)

    if args.list:
        print("Solvable (verified):", ", ".join(SOLVABLE))
        print("Experimental       : CF1B (fitted from confirmed pairs; see reverse_fit.py)")
        return 0
    if not args.system_number:
        ap.print_help()
        return 2

    try:
        pws, note = generate(args.system_number)
    except ValueError as e:
        print(f"error: {e}", file=sys.stderr)
        return 2

    for pw in pws:
        print(pw)
    if note:
        print(note, file=sys.stderr)
    if not pws and not note:
        print("(no password produced)", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
