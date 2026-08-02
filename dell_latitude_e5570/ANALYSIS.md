# Latitude E5570 (LA‑C841P) — EC firmware analysis

**Result: this 16 MiB SPI dump does not contain an EC firmware image.**
There is no EC region in the flash descriptor, and no Microchip/other EC image
anywhere in the BIOS after full decompression. The E5570's EC firmware lives on
a **separate, dedicated flash chip** that is not part of this dump.

## Flash layout (`flash_layout_16MB.txt`)

Single‑component 16 MiB image; the descriptor accounts for the entire chip with
no gaps and **no region index 8 (EC)**:

```
Idx Name                       Base        End          Size
  0 Flash Descriptor           0x00000000  0x00000FFF        4 KiB
  3 GbE                        0x00001000  0x00002FFF        8 KiB
  2 Intel ME                   0x00003000  0x006FFFFF     ~7 MiB   (cleared -> "CLEAR ME")
  1 BIOS                       0x00700000  0x00FFFFFF      ~9 MiB
  8 EC                         —  NOT PRESENT —
```

Because Descriptor→GbE→ME→BIOS are contiguous and fill the chip, there is
physically nowhere in this image for a separate EC region to hide.

## The BIOS was fully unpacked to check for an embedded EC image

The BIOS region was recursively extracted (`uefi-firmware-parser --superbrute`,
2 855 files, ~99 MiB of decompressed content). Searching **every decompressed
leaf** for a Microchip MEC image tag:

* `PHCM` (the Microchip MEC boot header used by the 3310): **0 hits.**

The only EC‑flavoured strings present are ordinary **BIOS‑side artifacts**, not an
EC image:

| Match | Where | What it actually is |
|---|---|---|
| `Base EC FW Version`, `Protocol Version` | a small DXE driver | BIOS reads/reports the EC version over its host interface |
| `MCHP` | ACPI (`_SB.PCI0.MCHP`) | the PCI host‑bridge ACPI device name, not Microchip EC |
| `SMSC` | ACPI SIO node list (`…CIRP.SMSC.W381…`) | Super‑I/O device naming in an ASL table |

i.e. the SPI image contains code that *talks to* the EC and describes it to the
OS, but not the EC's own firmware.

## Why

On these Skylake‑era Latitude **E‑series** boards (LA‑C841P / Compal) the EC is a
standalone SMSC/Microchip MEC with its **own SPI/flash**, programmed separately
from the mainboard boot flash. Dell ships EC updates for those inside the BIOS
*update package* (`.exe`/capsule), not persisted in the mainboard SPI region —
which is why a raw SPI dump of the boot flash has no EC image, unlike the
newer 3310 that maps a 1 MiB EC region into the shared flash.

## Takeaway

To recover the E5570 EC firmware "to readable source" you would need either a dump
of the EC's own flash chip, or the EC image extracted from a Dell BIOS update
package for this model — neither of which is present in the provided SPI dump.
The 3310 EC (which *is* in‑SPI) is fully unpacked in `../dell_latitude_3310/`.
