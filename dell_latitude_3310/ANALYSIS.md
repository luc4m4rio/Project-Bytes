# Latitude 3310 — EC firmware analysis

## Source dumps

The archive `DELL Latitude 3310 19717-1 BIOS 8th Gen CPU 8MB & 16MB BIOS`
contained two flash images. They are **two chips of a dual‑chip boot flash**, not
two copies of the same thing:

| File | Size | md5 | What it is |
|---|---|---|---|
| `D8M.bin`  | 8 MiB  | `e8ef5e2d…` | Descriptor + **EC** + ME chip (the descriptor/master chip) |
| `D16M.bin` | 16 MiB | `812e5fc5…` | The BIOS chip — a raw UEFI image, **no descriptor, no EC** |

`D8M.bin` has a valid Intel Flash Descriptor (`FLVALSIG 0x0FF0A55A` @ `0x10`)
describing a **2‑component** (dual‑chip) layout that spans a 24 MiB address space:

```
Idx Name                       Base        End          Size
  0 Flash Descriptor           0x00000000  0x00000FFF        4 KiB
  8 EC (Embedded Controller)   0x00001000  0x00100FFF        1 MiB   <-- target
  2 Intel ME                   0x00101000  0x007FFFFF     ~7 MiB
  1 BIOS                       0x00800000  0x017FFFFF       16 MiB   (lives on D16M chip)
```

So the EC firmware lives **only in `D8M.bin`**, region index 8, `0x1000`–`0x100FFF`.
`D16M.bin` starts with a UEFI firmware‑volume header at `0x28` and contains none of
descriptor / ME / EC — it is purely the 16 MiB BIOS region (confirmed: no `PHCM`
tag, no `FLVALSIG`). Full region tables: `flash_layout_D8M.txt`, `flash_layout_D16M.txt`.

## The EC container (`ec/`)

The carved 1 MiB region begins with the Microchip boot header — tag bytes
`50 48 43 4D` = **`PHCM`**, i.e. **`MCHP`** (Microchip) byte‑reversed. Decoded
(`ec/MEC_container_decode.txt`):

```
+0x00 Tag            b'PHCM'            (Microchip MEC boot image)
+0x08 Load address   0xBFCF0000         code is linked/loaded here
+0x0C Entry point    0xBFCF0001         (bit0 flag -> real entry 0xBFCF0000)
+0x10 Size           0x9B9 * 64 = 159296 bytes payload
+0x14 Payload offset 0x40               executable image starts here
+0x2C Checksum       0x4C844D7A
```

Embedded version block just past the header:

```
0x0146 Build date : 06/09/20
0x0150 EC version : 01.00.03
0x015A Build hash : 54f7e6206
0x0164 Copyright  : Copyright 1996-2020 Dell Inc.
```

Region map:

* `0x40 – 0x26E80` — executable image (159 296 B), loads to `0xBFCF0000`
* `0x26E80`        — 4‑byte image checksum trailer (`0x414825D8`)
* `0x34000 – 0x35A30`, `0x36000 – 0x3766F` — trailing config/data blocks
  (`ec/3310_D8M_EC_datablock_*.bin`)
* `0x38000 – 0x100000` — `0xFF` erase padding

## CPU architecture

Microchip MEC controllers use a Synopsys **ARC** core. Which ARC variant was
determined empirically, since it decides the disassembler:

* Base address `0xBFCF0000` is confirmed by ~480 internal `0xBFCF….` pointers in
  the image; the code is otherwise **PC‑relative / position‑independent** (no
  absolute pointers to strings — string loads use `add rX, pcl, off`).
* Disassembling the payload with the Synopsys GNU `objdump` and comparing CPU
  models, **`arc700` (ARCompact / ARCv1, little‑endian)** yields the cleanest
  decode (~79 % of the image is valid instructions; the rest is interleaved data).
  The tell‑tale ARCompact dispatcher at `0xBFCF2CFC` decodes perfectly:
  `ldw_s r2,[r12,0x6] / breq_s r13,0,N / bl_s …` — a command jump table.

So: **ARCompact (ARCv1), little‑endian, 32‑bit, load base `0xBFCF0000`, entry `0xBFCF0000`.**

## Readable source (`readable_source/`)

Two complementary artifacts — the objdump listing has complete instruction
coverage but is flat; the Ghidra output adds function structure and C but is
limited by the community SLEIGH module's opcode coverage.

* **`3310_EC_disasm_arc700.asm`** — full linear ARCompact disassembly (GNU
  `objdump -M cpu=arc700`), addresses at the real VMA `0xBFCF….`.
* **`3310_EC_decompiled.c`** — Ghidra recursive‑descent + decompiler, **541
  functions** to C. Functions are created at genuine call targets; `halt_*` /
  `asm_instruction_*` markers are opcodes the SLEIGH module does not yet model
  (surrounding logic is still valid).
* **`3310_EC_functions.txt`** — every recovered function (entry, size, name;
  `STUB` = decode‑degenerate).
* **`3310_EC_strings.txt`** — all strings with their region offsets.

### What the firmware does (from strings + decompilation)

The image is a full laptop EC. Recognisable subsystems include:

* **eSPI flash access** to the host — `ESpiRead/ESpiWrite/ESpiErase Flash busy!
  FLASH_CH_CONFIG=…`, `Espi_send_slave_boot_load fail!`, `LHI_PRI_QUE is Full!!`.
* **Dual‑firmware / recovery** — `Not running on FW1, processing switch.`,
  `POWER_ON: Flash Recovery Ctrl + Esc pressed`, `S5: bBOOT %08lx`.
* **Power / buttons / LEDs** — `Debounced, PWRB change`, `Turn on/off power
  button LED`, `Turn on/off AMBER LED`, `scan_leds_display_diags`,
  `paid_critical_power_off`.
* **GPIO / keyboard** — `GPIO %lx changed state to %d`, `typematic rate`,
  `GetLidSwitchEnable`.
* **Battery / smart‑battery** — `dellbatterydell`, `VerifyEcSdsaSignature`,
  vendor table `SANYO / PANASONIC / SAMSUNG SDI / MOTOROLA`.
