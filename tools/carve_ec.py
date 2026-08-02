#!/usr/bin/env python3
"""Carve the Embedded Controller (EC) firmware out of an Intel SPI flash dump.

Given a full SPI flash image that has an EC region declared in its Intel Flash
Descriptor (region index 8), this:
  1. parses the descriptor and locates the EC region,
  2. writes the raw EC region,
  3. parses the Microchip "MCHP"/"PHCM" boot header,
  4. writes the executable payload (the image that the MEC boot ROM loads).

Usage:  python3 carve_ec.py <flash_dump.bin> <out_dir>
"""
import sys, os, struct

def u32(b, o): return struct.unpack_from("<I", b, o)[0]

def find_descriptor(data):
    for off in (0x10, 0x00):
        if len(data) >= off + 4 and u32(data, off) == 0x0FF0A55A:
            return off - 0x10
    for off in range(0, min(len(data), 0x1000) - 4, 4):
        if u32(data, off) == 0x0FF0A55A:
            return off - 0x10
    return None

def ec_region(data):
    base = find_descriptor(data)
    if base is None:
        return None
    frba = ((u32(data, base + 0x14) >> 16) & 0xFF) << 4
    flreg8 = u32(data, base + frba + 8 * 4)          # region 8 = EC
    r_base = (flreg8 & 0x7FFF) << 12
    r_end = (((flreg8 >> 16) & 0x7FFF) << 12) | 0xFFF
    if (flreg8 & 0x7FFF) == 0x7FFF or r_end < r_base:
        return None
    return r_base, r_end

def main():
    if len(sys.argv) != 3:
        print(__doc__); sys.exit(1)
    path, outdir = sys.argv[1], sys.argv[2]
    os.makedirs(outdir, exist_ok=True)
    data = open(path, "rb").read()
    reg = ec_region(data)
    if not reg:
        print("No EC region (idx 8) in this dump's flash descriptor.")
        sys.exit(2)
    b, e = reg
    ec = data[b:e + 1]
    ecpath = os.path.join(outdir, f"EC_region_0x{b:X}-0x{e:X}.bin")
    open(ecpath, "wb").write(ec)
    print(f"EC region  : 0x{b:X}..0x{e:X}  ({len(ec)} bytes) -> {ecpath}")

    if ec[:4] != b"PHCM":
        print("EC region present but no MCHP/PHCM header; wrote raw region only.")
        return
    load = u32(ec, 0x08)
    poff = u32(ec, 0x14)
    plen = u32(ec, 0x10) * 64
    payload = ec[poff:poff + plen]
    ppath = os.path.join(outdir, f"EC_code_loaded_base0x{load:08X}.bin")
    open(ppath, "wb").write(payload)
    print(f"MCHP header: load=0x{load:08X} payload_off=0x{poff:X} size={plen}")
    print(f"Payload    : {len(payload)} bytes -> {ppath}  (disassemble as ARCompact:LE:32 @ 0x{load:08X})")

if __name__ == "__main__":
    main()
