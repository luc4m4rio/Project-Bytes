# Locating the BIOS unlock / master-password check (SystemBIOS 1.19.1)

## The validation model ("the black box")

The user-facing setup/unlock prompt accepts a **16-character** password, submitted
with a dedicated hotkey, and hands it off to a **System Management Mode (SMM)**
handler over an SMI — a separate execution context from the setup UI. The handler
does not store the password in clear text. Instead it derives the expected value:

```
digest      = SHA-256( serviceTag(7 chars) || familyTag(4 chars) )   # 32 bytes
expected16  = memcpy(digest, 16)                                      # first 128 bits
accept      = (userInput16 == expected16)
```

- **32 → 16 truncation**: the handler `memcpy`s the first 16 of the 32 SHA-256
  output bytes and compares that against the input.
- **7-char unique identifier**: the Dell **Service Tag** (Dell service tags are
  exactly 7 chars), read from SMBIOS.
- **4-char family tag**: a platform-specific suffix, **one of a small fixed set
  (~5)** across the encoded family. The exact suffix for this platform must be
  read out of the binary — do not assume it.

This is the Dell service-tag master/recovery password scheme (owner lock-out
recovery). Everything below is about *finding the module that implements it*
in this firmware image.

## What's committed vs. what's needed

Committed here: the UEFIExtract **structure report** and **GUID list** only. The
firmware `.bin`, the UEFIExtract `.dump`, and the extracted PE images are
`.gitignore`d (see repo root `.gitignore`) and are **not** in the tree, so the
module bytes cannot be disassembled from the checkout alone.

The report identifies modules **by GUID only** — UEFIExtract resolved no friendly
names for the DXE/SMM drivers here. Inventory (from the committed report):

- 585 PE-bearing modules total — **341 DXE drivers, 157 SMM modules, 87 PEI modules**

That is far too many to eyeball, and the password check is one SMM driver among
157. So we locate it by **content fingerprint**, not by name.

## How to locate it

### Step 1 — regenerate the extracted modules

The dump is reproducible from the pipeline:

```bash
analysis/scripts/extract_pipeline.sh --skip-pfs firmware/input/SystemBIOS_1.19.1.bin
# -> firmware/extracted/pe_images/SystemBIOS_1.19.1/   (the PE images to scan)
```

### Step 2 — fingerprint-rank the candidates

`analysis/scripts/locate_password_check.py` ranks every module by three signals:

1. **SHA-256 constant tables** (H-init `6a09e667…` and K-round `428a2f98…`,
   both byte orders) — a hard fingerprint present in any SHA-256 implementation.
   Strongest signal (the "black box" is SHA-256).
2. **Family tag strings** — the candidate 4-char suffixes (ASCII + UTF-16LE).
3. **Service-tag / SMBIOS strings** — `Service Tag`, `ServiceTag`, `Serial
   Number`, etc.

```bash
analysis/scripts/locate_password_check.py --scan firmware/extracted/pe_images/SystemBIOS_1.19.1/
# override the suffix candidates once you know the family:
analysis/scripts/locate_password_check.py --scan <dir> --tags 1F66,6FF1,1D3B,2A7B,BF97
```

The module that combines a SHA-256 table **with** a family-tag/service-tag string
is the prime suspect. A module with only the SHA-256 table is likely the shared
crypto library (e.g. `CryptoSmm`/BaseCryptLib) that the real handler *calls* — a
useful lead, not the target.

Without any bytes, you can still inventory the module list straight from the report:

```bash
analysis/scripts/locate_password_check.py --from-report firmware/extracted/uefi/SystemBIOS_1.19.1.bin.report.txt
```

### Step 3 — confirm in Ghidra

Import the prime suspect (the Stage-3 Ghidra pipeline already does this), then:

1. Find the SHA-256 routine (its constant table is the anchor) and look at its
   **callers**.
2. In the calling function, look for a **16-byte compare** immediately after the
   digest is produced — `CompareMem(a, b, 0x10)`, an unrolled two-`QWORD` compare,
   or a `rep cmpsb`/loop with count `0x10`. That 16 (`0x10`), not 32, is the
   truncation tell.
3. Trace the two hash inputs back: one should resolve to an SMBIOS service-tag
   read (7 chars), the other to a static **4-char** string constant — that string
   **is** this platform's family tag. Record it.
4. The buffer being compared against the digest is the user input arriving from
   the setup UI via the SMI (look for the SMI dispatch registration / comm buffer).

## Candidate narrowing hints

- The check is a **Dell-proprietary SMM driver**, not the generic AMI admin/user
  password path. Named Dell modules in the GUID list worth correlating:
  `DellUnzipDriver`, `DellJSONParserDriver`, `DellBcRcvExtractor`,
  `DellNetworkTransferDriver`, `DellSupportAssistUi`, `DellRamDisk`
  (`firmware/extracted/uefi/SystemBIOS_1.19.1.bin.guids.csv`). The password
  handler will sit among the *unnamed* Dell SMM drivers alongside these.
- The AMI setup UI is `AMITSE` (`B1DA0ADF-…`) with vars `AMITSESetup` /
  `AMITSESetupData` — that's the prompt front-end, not the service-tag derivation.
- SMM `CryptoSmm`/BaseCryptLib will also match the SHA-256 fingerprint; expect it
  to rank high but carry **no** family-tag/service-tag strings. Use it to find the
  caller, don't mistake it for the target.

## Status / open items

- [ ] Commit or stage the `.bin` locally, regenerate the dump, run the scanner.
- [ ] Confirm the prime-suspect GUID and record it here.
- [ ] Read out the **exact** 4-char family tag and the SHA-256 input byte order.
- [ ] Read out the **byte→character encoding** that renders the 16 digest bytes
      into the 16-char password alphabet (needed for a byte-exact reference impl;
      not derivable from the report — only from the disassembly).
