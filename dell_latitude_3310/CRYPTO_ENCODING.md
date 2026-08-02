# Latitude 3310 EC — crypto & encoding functions

Identification of the cryptographic and encoding routines in the 3310 EC image
(`ec/3310_D8M_EC_code_loaded_base0xBFCF0000.bin`, ARCompact LE, base `0xBFCF0000`).

Primitives are identified from their **standard constant tables and strings**, which
are unambiguous fingerprints, and verified byte‑for‑byte against reference
implementations. Addresses are given both as flash‑region offsets (in the carved
1 MiB EC region) and as runtime VMAs.

| # | Primitive | Evidence | Region off | VMA |
|---|---|---|---|---|
| 1 | **SHA‑256** | full **64/64** round‑constant table `K[0..63]` (0x428a2f98 …) | `0x184F0` | `0xBFD084B0` |
| 2 | **CRC‑32** (IEEE, reflected) | full **256/256** standard lookup table + polynomial `0xEDB88320` | `0xADBC` (poly `0xAFBC`) | `0xBFCFAD7C` (poly `0xBFCFAF7C`) |
| 3 | **Signature verification** (`VerifyEcSdsaSignature`) | routine name + self‑timing (`"…used %d ms"`) | `0x14E08` | `0xBFD04DC8` |
| 4 | **Integer → ASCII encoding** (itoa / printf radix) | digit table `0123456789abc…xyzABC…XYZ` | `0x22DAC` | `0xBFD12D6C` |
| 5 | **Smart‑battery authentication** | `dellbatterydell` tag (×2) + vendor table `SANYO/PANASONIC/…` | `0x14E38`, `0x15354` | `0xBFD04DF8`, `0xBFD05314` |

## 1. SHA‑256

The complete, standard SHA‑256 message‑schedule constant table `K[0..63]`
(`0x428a2f98, 0x71374491, 0xb5c0fbcf, …, 0xc67178f2`) is present verbatim at
`0xBFD084B0` — a **64/64** exact match. This is a definitive SHA‑256 fingerprint.
The eight initial hash values `H0..H7` are not stored as a contiguous block, which
is normal: they are materialised as immediates inside the hash‑init routine.
SHA‑256 is the digest used by the signature‑verification path (#3).

## 2. CRC‑32 (IEEE 802.3, reflected)

A full 256‑entry standard reflected CRC‑32 lookup table sits at `0xBFCFAD7C`
(table[0]=0, table[1]=`0x77073096`, … — **256/256** match), with the reflected
polynomial constant `0xEDB88320` at `0xBFCFAF7C`. This is a classic table‑driven
`crc = table[(crc ^ byte) & 0xFF] ^ (crc >> 8)` implementation, used for image /
block integrity (the MCHP container itself carries a checksum trailer, and the eSPI
flash paths report `FLASH_CH_STATUS`).

## 3. Firmware / image signature verification — `VerifyEcSdsaSignature`

`VerifyEcSdsaSignature used %d ms` — the routine hashes an image (SHA‑256, #1) and
verifies a **SDSA** ("Secure Digital Signature Algorithm", Dell's term) signature
before accepting it. It is the secure‑boot / secure‑update gate, tied to the
dual‑image machinery seen in the strings:

* `Espi_send_slave_boot_load fail!` (`0xBFCFA02C`) — sending the verified boot
  image to the host over eSPI slave‑boot,
* `Not running on FW1, processing switch.` (`0xBFD157D4`) — A/B firmware bank switch,
* `POWER_ON: Flash Recovery Ctrl + Esc pressed` — recovery entry.

The `SDSA` verify combines the SHA‑256 digest with a public‑key check; on Microchip
MEC parts the modular‑exponentiation / ECDSA step is typically offloaded to the
on‑die Public‑Key Engine, which is why no large software big‑integer loop appears
in the recovered code.

## 4. Integer → ASCII encoding (itoa / printf radix conversion)

The digit table `0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ`
at `0xBFD12D6C` is the alphabet for base‑N number→string conversion (it backs the
`%d/%u/%x` formatting used throughout the log strings, e.g. `GPIO %lx changed state`,
`S5: bBOOT %08lx`). The formatter lives in the `0xBFD12Bxx` region
(`FUN_ram_bfd12b32` accesses this table).

## 5. Smart‑battery authentication

`dellbatterydell` (present twice, `0xBFD04DF8` and `0xBFD0525C`) is Dell's
battery‑authentication tag, adjacent to the battery‑vendor table
`SANYO / PANASONIC / SAMSUNG SDI / MOTOROLA` (`0xBFD05314`). The EC authenticates
the pack by running `VerifyEcSdsaSignature` (#3) over a battery challenge — the
`FUN_ram_bfd04ae0` / `FUN_ram_bfd05200` region references this data.

## Method & caveats

* Primitives (#1, #2) are proven by exact table matches — not heuristics.
* The EC is ARCompact using **gp‑relative and PC‑relative** addressing, so table and
  string *addresses never appear as literals* in the code (only signed offsets from
  `gp`). Combined with the community ARCompact SLEIGH module's incomplete opcode
  coverage (`asm_instruction_*` markers), this means the crypto **data** is pinned
  exactly but the exact function *entry points / clean bodies* are only partially
  recovered — the function associations above are given where recoverable.
* Not found: no AES S‑box / inverse S‑box, no MD5/SHA‑1 constants, no RC4/DES
  fingerprints. The crypto surface is SHA‑256 + CRC‑32 + the SDSA signature verify.

Reproduce the constant scan with `tools/sigscan.py` and the byte‑exact checks in
this directory's analysis history.
