# Dell Latitude EC region unpack

Unpacking the **Embedded Controller (EC) regions / firmware** out of two Dell
Latitude SPI flash dumps, all the way down to readable source (annotated
ARCompact disassembly + Ghidra C decompilation).

| Machine | Board | Dump(s) | EC firmware in SPI? |
|---|---|---|---|
| **Latitude 3310** | 19717-1 (8th Gen) | `D8M.bin` (8 MiB), `D16M.bin` (16 MiB) | **Yes** — dedicated 1 MiB EC region |
| **Latitude E5570** | LA‑C841P (Skylake) | `16MB_.bin` (16 MiB, ME cleared) | **No** — EC lives on a separate chip |

The two source archives were full SPI flash dumps of the mainboard boot flash
(Intel PCH SPI). On Intel platforms the flash is partitioned by the
**Intel Flash Descriptor** into regions (Descriptor / BIOS / ME / GbE / … / **EC**).
The goal here was region index **8 = Embedded Controller**.

---

## TL;DR result

* **Latitude 3310** — the EC firmware is a **Microchip MEC** (Synopsys **ARCompact / ARCv1**,
  little‑endian) image sitting in the dedicated EC region of `D8M.bin`
  (`0x1000`–`0x100FFF`, 1 MiB). It carries the Microchip `MCHP`/`PHCM` boot header,
  loads to VMA `0xBFCF0000`, and is **Dell EC firmware v01.00.03 (build 06/09/20)**.
  It has been carved, its container decoded, and the code taken to readable source:
  * `dell_latitude_3310/readable_source/3310_EC_disasm_arc700.asm` — full GNU objdump
    ARCompact disassembly (mature GNU ARC decoder; ~79 % of the image decodes as code,
    the rest is interleaved data tables/strings).
  * `dell_latitude_3310/readable_source/3310_EC_decompiled.c` — **541 functions**
    decompiled to C by Ghidra using the community ARCompact SLEIGH module.

* **Latitude E5570** — the 16 MiB SPI dump contains **no EC region and no EC
  firmware image**. Its flash descriptor accounts for the whole chip
  (Descriptor + GbE + ME + BIOS, no gaps, no region 8), and after fully
  decompressing every BIOS firmware volume there is **no Microchip `PHCM` image**
  anywhere — only BIOS‑side EC *drivers* and ACPI device nodes. On this
  E‑series board the EC (an SMSC/Microchip MEC) has its **own dedicated flash
  chip** that is not part of this dump. Details and evidence in
  `dell_latitude_e5570/ANALYSIS.md`.

---

## Layout of this repo

```
tools/                         reproducible tooling
  ifd.py                       Intel Flash Descriptor parser (region table)
  carve_ec.py                  carve EC region + MEC payload from a full dump
  sigscan.py                   scan a blob for EC/ME/UEFI signatures
  crypto_scan.py               scan a blob for crypto/encoding fingerprints
  disassemble_ec.sh            objdump + Ghidra headless driver
  ghidra_scripts/              SeedDisasm.java, ExportEC.java (headless)
  ghidra_arc_module/ARC/       community ARCompact SLEIGH module (drop into Ghidra)

dell_latitude_3310/
  flash_layout_D8M.txt         descriptor/region table of the 8 MiB dump
  flash_layout_D16M.txt        the 16 MiB dump = BIOS‑only image (no descriptor/EC)
  ec/
    3310_D8M_EC_region_0x1000-0x100FFF.bin   raw 1 MiB EC region (carved)
    3310_D8M_EC_code_loaded_base0xBFCF0000.bin  executable payload (disasm target)
    3310_D8M_EC_datablock_0x34000.bin        trailing config/data block
    3310_D8M_EC_datablock_0x36000.bin        trailing config/data block
    MEC_container_decode.txt                 decoded MCHP header + version block
  readable_source/
    3310_EC_disasm_arc700.asm                objdump ARCompact disassembly
    3310_EC_decompiled.c                     Ghidra C decompilation (541 funcs)
    3310_EC_functions.txt                    function table (addr, size, name)
    3310_EC_strings.txt                      strings with region offsets
  ANALYSIS.md
  CRYPTO_ENCODING.md          crypto & encoding primitives (SHA-256, CRC-32, SDSA verify…)

dell_latitude_e5570/
  flash_layout_16MB.txt        descriptor/region table (no EC region)
  ANALYSIS.md                  why there is no EC firmware in this SPI dump
```

The full 8/16 MiB vendor SPI dumps themselves are **not** committed (they are the
raw inputs and are large); everything needed to reproduce the carve from them is
in `tools/` and documented per machine.

---

## Reproducing

Toolchain used (Ubuntu 24.04):

```bash
# archive + firmware tooling
apt-get install -y unrar p7zip-full flex texinfo
pip3 install uefi_firmware

# ARC disassembler (Synopsys prebuilt GNU toolchain, elf32 LE)
#   github.com/foss-for-synopsys-dwc-arc-processors/toolchain (arc-2021.09-release)
#   -> arc-snps-elf-objdump / -objcopy

# Ghidra 11.x + community ARCompact SLEIGH module
#   github.com/NationalSecurityAgency/ghidra (release)
#   module from niooss-ledger/ghidra @ arcompact : Ghidra/Processors/ARC
#   (a copy is vendored in tools/ghidra_arc_module/ARC)
cp -r tools/ghidra_arc_module/ARC $GHIDRA_HOME/Ghidra/Processors/ARC
$GHIDRA_HOME/support/sleigh $GHIDRA_HOME/Ghidra/Processors/ARC/data/languages/ARCompact.slaspec
```

Then, from a full SPI dump:

```bash
python3 tools/ifd.py         D8M.bin                 # inspect regions
python3 tools/carve_ec.py    D8M.bin  out/           # carve EC region + payload
ARC_BIN=/opt/arc/.../bin GHIDRA_HOME=/opt/ghidra_11.3.2_PUBLIC \
  tools/disassemble_ec.sh out/EC_code_loaded_base0xBFCF0000.bin 0xBFCF0000 out/
```

## Credits / notes

* ARCompact SLEIGH module: Nicolas Iooss (Ledger Donjon), *“Analyzing ARCompact
  firmware with Ghidra”*, SSTIC 2021 — vendored under `tools/ghidra_arc_module/`.
* ARC GNU toolchain: Synopsys `foss-for-synopsys-dwc-arc-processors`.
* The firmware is Dell/Microchip property; it is analysed here for
  interoperability/repair research on hardware in the owner's possession.
