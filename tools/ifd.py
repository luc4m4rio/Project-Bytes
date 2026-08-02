#!/usr/bin/env python3
"""Minimal Intel Flash Descriptor (IFD) parser.

Locates region layout of an Intel SPI flash dump and prints the region table,
with special attention to the EC (Embedded Controller) region.
"""
import sys, struct

REGION_NAMES = {
    0: "Flash Descriptor",
    1: "BIOS",
    2: "Intel ME",
    3: "GbE",
    4: "Platform Data (PDR)",
    5: "Device Expansion 1",
    6: "Secondary BIOS (BIOS2)",
    7: "Microcode",
    8: "EC (Embedded Controller)",
    9: "Device Expansion 2",
    10: "IE",
    11: "10GbE 0",
    12: "10GbE 1",
    13: "Reserved 13",
    14: "Reserved 14",
    15: "PTT / Reserved 15",
}

def u32(b, off):
    return struct.unpack_from("<I", b, off)[0]

def find_descriptor(data):
    """Return offset of FLVALSIG 0x0FF0A55A. Normally 0x10."""
    for off in (0x10, 0x00):
        if len(data) >= off+4 and u32(data, off) == 0x0FF0A55A:
            return off - 0x10  # base of descriptor
    # brute scan first 0x1000
    for off in range(0, min(len(data), 0x1000)-4, 4):
        if u32(data, off) == 0x0FF0A55A:
            return off - 0x10
    return None

def parse(data):
    base = find_descriptor(data)
    if base is None:
        return None
    flmap0 = u32(data, base+0x14)
    flmap1 = u32(data, base+0x18)
    flmap2 = u32(data, base+0x1C)
    fcba = (flmap0 & 0xFF) << 4
    nc   = ((flmap0 >> 8) & 0x3) + 1
    frba = ((flmap0 >> 16) & 0xFF) << 4
    fmba = (flmap1 & 0xFF) << 4
    nm   = ((flmap1 >> 8) & 0x7)
    info = dict(base=base, flmap0=flmap0, flmap1=flmap1, flmap2=flmap2,
               fcba=fcba, nc=nc, frba=frba, fmba=fmba)
    regions = []
    for i in range(16):
        off = base + frba + i*4
        if off+4 > len(data):
            break
        flreg = u32(data, off)
        r_base = (flreg & 0x7FFF) << 12
        r_limit = ((flreg >> 16) & 0x7FFF) << 12
        # region present if not the "empty" encoding (base 0x7FFF..., limit 0)
        base_field = flreg & 0x7FFF
        limit_field = (flreg >> 16) & 0x7FFF
        if base_field == 0x7FFF and limit_field == 0:
            present = False
            size = 0
            end = None
        elif flreg == 0xFFFFFFFF:
            present = False
            size = 0
            end = None
        else:
            present = (limit_field >= base_field)
            end = r_limit + 0xFFF  # inclusive end
            size = (end - r_base + 1) if present else 0
        regions.append(dict(idx=i, flreg=flreg, base=r_base, end=end,
                            size=size, present=present,
                            name=REGION_NAMES.get(i, f"Region {i}")))
    info["regions"] = regions
    return info

def component_size_str(data, info):
    # Flash component section: FLCOMP at fcba
    flcomp = u32(data, info["base"]+info["fcba"])
    dens = flcomp & 0x7
    dmap = {0:"512KiB",1:"1MiB",2:"2MiB",3:"4MiB",4:"8MiB",5:"16MiB",6:"32MiB",7:"64MiB"}
    return f"FLCOMP=0x{flcomp:08X} comp0_density={dmap.get(dens,'?')}"

def main():
    path = sys.argv[1]
    with open(path,"rb") as f:
        data = f.read()
    print(f"File: {path}")
    print(f"Size: {len(data)} bytes (0x{len(data):X}, {len(data)//1024//1024} MiB)")
    info = parse(data)
    if not info:
        print("  !! No valid Intel Flash Descriptor found (FLVALSIG 0x0FF0A55A missing).")
        return
    print(f"Descriptor base: 0x{info['base']:X}")
    print(f"FLMAP0=0x{info['flmap0']:08X} FLMAP1=0x{info['flmap1']:08X} FLMAP2=0x{info['flmap2']:08X}")
    print(f"FCBA=0x{info['fcba']:X}  NumComponents={info['nc']}  FRBA=0x{info['frba']:X}  FMBA=0x{info['fmba']:X}")
    try:
        print(component_size_str(data, info))
    except Exception as e:
        print(f"FLCOMP parse err: {e}")
    print("")
    print(f"{'Idx':>3} {'Name':<26} {'Base':>10} {'End':>10} {'Size':>12} {'FLREG':>10}  Present")
    print("-"*90)
    for r in info["regions"]:
        ends = f"0x{r['end']:08X}" if r['end'] is not None else "--"
        print(f"{r['idx']:>3} {r['name']:<26} 0x{r['base']:08X} {ends:>10} "
              f"{r['size']:>12} 0x{r['flreg']:08X}  {'YES' if r['present'] else '-'}")
    print("")
    ec = info["regions"][8]
    if ec["present"] and ec["size"]>0:
        print(f">>> EC region: base=0x{ec['base']:X} end=0x{ec['end']:X} size={ec['size']} (0x{ec['size']:X}) bytes")
    else:
        print(">>> EC region (idx 8): NOT present in descriptor.")

if __name__ == "__main__":
    main()
