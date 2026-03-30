# Dell Latitude 7X00 BIOS v1.19.1 — Firmware RE Findings
## Project: Dell 8FC8 / NVRAM Password Analysis

---

## 1. Firmware Image Info

| Field | Value |
|-------|-------|
| File | `Latitude_7X00_1.19.1.exe` |
| SHA256 | `73545b226af5db7e27ff95674b64d386eccecb5cf7b7ad575c505424dad41249` |
| PE images extracted | 589 |
| Architecture | x86-64 EFI (DXE / SMM modules) |

---

## 2. Critical Modules Identified

### 2.1 PE_0119 — AMI TSE (Text Setup Environment) ★ PRIMARY TARGET ★

| Field | Value |
|-------|-------|
| GUID | `EE4E5898-3914-4259-9D6E-DC7BD79403CF` / AMI TSE |
| Path | `5C60F367.../426 AMITSE/EE4E5898.../0 PE32 image section` |
| Size | 523 KB (885 functions) |
| Arch | x86-64 |

**Key strings:**
- `u"DellPassword"` @ 0x00060050 — NVRAM variable name
- `u"LinkDellPasswordData"` @ 0x0006AD10 — protocol name
- `u"Incorrect Password Entered"` @ 0x0006A710
- `u"Incorrect Password. One Try Remaining."` @ 0x0006A790
- `u"Incorrect Password Entered. Please Try Again."` @ 0x0006A810
- `u"Enter Admin Password, Then [Enter], to Continue"` @ 0x0006A910
- `u"BIOS Setup"`, `u"BIOS Flash Update"` — UI entry points
- `"BIOS Revision 1.19.1"` — version confirmation

**Significance:** AMITSE is the AMI BIOS authentication driver. It owns:
- Password entry prompt rendering
- DellPassword NVRAM variable read/write
- LinkDellPasswordData protocol installation
- Admin/System/HDD password authentication flow

---

### 2.2 PE_0186 — DXE-to-SMM Context Transfer / AMI Setup R/W ★★ KEY FINDING ★★

| Field | Value |
|-------|-------|
| GUID | `34E74B1B-8794-4402-AA43-99B5249B1CFD` |
| Size | 39 KB |
| Arch | x86-64 |

**`FUN_00001b58` — AMI Setup NVRAM R/W (THE critical function):**

```c
// GUID: EC87D643-EBA4-4BB5-A1E5-3F3E36B20DA9
// Variable: "Setup", Size: 0x17fd (6141) bytes
// EFI_RUNTIME_SERVICES base in DAT_0000a888

local_1818 = 0xec87d643;  // GUID data1
local_1814 = 0xeba4;      // GUID data2
local_1812 = 0x4bb5;      // GUID data3
// data4: a1 e5 3f 3e 36 b2 0d a9

// Read: (**(code**)(DAT_0000a888 + 0x48))(...)  ← GetVariable
// Write: (**(code**)(DAT_0000a888 + 0x58))(...)  ← SetVariable

// Password state flag:
local_5cc = ~-(ushort)(local_359 != '\0') & 2;
//  → 0x0002 if password IS set (local_359 != 0)
//  → 0x0000 if password NOT set
```

**Password flag: byte at offset 0x359 within the 6141-byte "Setup" NVRAM blob.**

---

### 2.3 PE_0433 — HII Setup Forms Module

| Field | Value |
|-------|-------|
| GUID | `EA907DA1-4A74-80B8-A66E-BAA384223E12` |
| Size | 127 KB (13 functions) |
| Arch | x86-64 |

**Significance:** Pure HII data module (BIOS setup form definitions). Contains descriptive strings for all password-related BIOS settings:
- `DellPassword`, `PasswordBypass`, `PasswordLock`, `StrongPassword`
- `AdminPasswordMinLen/MaxLen`, `SystemPasswordMinLen/MaxLen`
- `"SMM Security Mitigation"` description text
- Password bypass documentation

This module is NOT code — it is IFR (Internal Form Representation) data that AMITSE interprets.

---

### 2.4 PE_0529 — BIOS POST Core Module

| Field | Value |
|-------|-------|
| GUID | `D1068F86-B9E6-43A6-A50A-7BCA298D537E` |
| Size | 1.1 MB (1966 functions) |
| Arch | x86-64 |

**Key strings:** "Password Setup", "Boot/Disk password incorrect", "NVRAM Data Invalid/Checksum Error"

**Findings:**
- Password/NVRAM strings stored in POST message table (accessed by index, no direct XRefs)
- HII form builders: `FUN_00045188`, `FUN_000466ac`
- EFI services via pointer tables: `DAT_00101ac0` (EFI_SYSTEM_TABLE), `DAT_001019a0`, `DAT_00101ac8`

---

### 2.5 PE_0072 — SATA/Storage + DXE-to-SMM Infrastructure

| Field | Value |
|-------|-------|
| GUID | `E5E2C9D9-5BF5-497E-8860-94F81A09ADE0` (DXETOSMMH9) |
| Size | 12.5 KB |
| Arch | x86-64 |

**`FUN_00001dd8`:** Gets SMM system table via SmmBase2 protocol, allocates 0x22d28 bytes in SMM pool, registers SMI handler `FUN_00001d84`.

**`FUN_00001d84`:** Registers callback `FUN_00002ba8` as a protocol notification handler. DXE-to-SMM communication channel.

---

### 2.6 PE_0233 — Boot Manager / DXE Core

| Field | Value |
|-------|-------|
| GUID | `E94F54CD-81EB-47ED-AEC3-856F5DC157A9` |
| Size | 61 KB |
| Arch | x86-64 |

**`FUN_00003c74`:** Main boot image loading loop (LoadImage/StartImage).

**`thunk_FUN_0000c138`:** Hardware I/O — CMOS (0x70/0x71), PCI config (0xCF8), IOAPIC (0xFEC00000). Not directly password-related.

---

### 2.7 PE_0198 — ME Password/Hash Manager

| Field | Value |
|-------|-------|
| GUID | `9CFD802C-09A1-43D6-8217-AA49C1F90D2C` |
| Size | 103 KB |
| Arch | x86-64 |

**Key strings:** `"Change ME Password"`, AMT provisioning flow

**Protocol interface at `DAT_000186f8`:**
- +0x18: QueryProtocol?
- +0x20: SetValue
- +0x28: CommitValue
- +0x30: GetHandle
- +0x40: MEBx interface pointer
- +0x48: Count field

This module manages ME BIOS Extension password (separate from Admin/System passwords).

---

### 2.8 PE_0309 — Unknown (GUID `899407D7-99FE-43D8-9A21-79EC328CAC21`)

| Field | Value |
|-------|-------|
| Size | ~1 MB (389+ functions) |
| Arch | x86-64 |

**Key strings:** `u"Passwords do not match."` @ 0x00029610

**Raw memory:** `DellPassword.$!...6...K.1.z...k....AmiTseMode.$)` at 0x0003CCC3 — DellPassword and AmiTseMode variable names embedded in HII data table.

---

## 3. AMI Setup NVRAM Variable Layout

**Variable:** `"Setup"` / GUID `EC87D643-EBA4-4BB5-A1E5-3F3E36B20DA9` / 6141 bytes

| Offset | Size | Description |
|--------|------|-------------|
| 0x000 | ... | General setup options |
| 0x359 | 1   | **Password state flag** (0=no password, non-zero=password set) |
| ...   | ... | Other setup options |
| 0x17FC | 1  | End of blob |

The flag at 0x359 controls the bitmask computed in `FUN_00001b58`:
```
result_bit = ~-(ushort)(flag != '\0') & 2  →  2 if set, 0 if clear
```

---

## 4. Password Authentication Flow (Reconstructed)

```
BIOS POST boot
    │
    ├─► PE_0186:FUN_00001b58
    │       GetVariable("Setup", EC87D643...) → 6141-byte blob
    │       Check blob[0x359] → password state flag
    │       SetVariable if modified
    │
    └─► PE_0119 (AMI TSE) ← PRIMARY AUTHENTICATION
            Read "DellPassword" NVRAM variable
            Display password entry prompt
            Compare entered password
                ├─ Incorrect → show error string + retry counter
                └─ Correct   → unlock BIOS setup / continue boot
```

**TODO:** Trace the actual hash comparison within PE_0119.

---

## 5. DellPassword NVRAM Variable

**Name:** `"DellPassword"` (Unicode) — accessed by PE_0119
**Protocol:** `"LinkDellPasswordData"` — likely a GUID protocol that PE_0119 installs to share password state with other DXE drivers

The DellPassword variable is separate from the AMI "Setup" variable. It likely contains:
- Hashed Admin/System password(s)
- Password policy flags (StrongPassword, MinLen, MaxLen)
- Possibly the hash algorithm identifier

---

## 6. Dell 8FC8 Challenge/Response

The Dell 8FC8 system is a recovery/bypass mechanism for forgotten BIOS passwords. Based on the analysis:

1. A "challenge code" is derived from the BIOS service tag + password attempt count
2. The vendor (Dell support) computes a "response code" using an internal algorithm
3. The response allows bypassing the Admin password check

The challenge generation likely occurs in PE_0119 (AMI TSE) or a dependent protocol. The hash/response computation is likely in an SMM-resident handler not yet identified.

---

## 7. Complete Password Authentication Call Chain (CONFIRMED)

```
User enters password at BIOS prompt
    │
    └─► PE_0119 (AMI TSE) FUN_0005b220
            1. Build LinkDellPasswordData buffer (0x44 bytes)
               - cmd byte at offset 0x10 (0=verify Admin, 1=set Admin, 2=clear, 5=verify HDD...)
               - password string / hash in buffer
            2. SetVariable("LinkDellPasswordData", GUID C8BD7E42, buf)
            3. out(0xb2, 0xaf)   ← trigger SMI 0xAF
            │
            └─► PE_0255 SMI handler LAB_000011a0
                    GetVariable("LinkDellPasswordData") → read cmd byte
                    Dispatch by cmd:
                      cmd 0 → FUN_00002254(buf, BIOS_PW_GUID, 0) ← verify admin
                      cmd 1 → FUN_00002254(buf, BIOS_PW_GUID, 1) ← set admin
                      cmd 2 → FUN_00002254(buf, BIOS_PW_GUID, 2) ← clear admin
                      cmd 5 → FUN_00002254(buf, HDD_PW_GUID, 3)  ← verify HDD
                    │
                    └─► FUN_000020a0: LocateProtocol(PasswordHandlerProto=0AB697CE)
                        enumerate handles → find matching GUID + cmd
                        call interface→method(buf, result)
                            │
                            └─► PE_0516 FUN_00001bd8 (verify callback)
                                    FUN_00002798(local_58, 0x20, password, len)
                                    ← copies plaintext password into 32-byte buffer
                                    │
                                    ├─► PE_0463 3A441BF0 proto +0x10
                                    │       Hash(entered_password) → stored
                                    │
                                    └─► PE_0463 3A441BF0 proto +0x08
                                            FUN_000026c4: compare hashes
                                            FUN_0000232c: get stored SHA-256 hash
                                            FUN_000044a0: memcmp(entered_hash, stored_hash, 32)
                                            ↑ Return 0 = correct password
                    SetVariable("LinkDellPasswordData", result byte)
            4. GetVariable("LinkDellPasswordData") → read result
            5. if buf[0] == 0xFF, buf[1] == 0x11 → success
```

---

## 7a. Password Hash Algorithm (CONFIRMED)

**Algorithm:** SHA-256 with fixed 4-byte salt

```
stored_hash = SHA-256(plaintext_password || 0x8d_fc_7b_25)
```

**Implementation:** PE_0463 `FUN_00001bb4`
```c
FUN_00003c40(sha256_ctx);               // SHA-256_Init
FUN_00003d18(ctx, password, len);       // SHA-256_Update(password)
FUN_00003d18(ctx, 0x8dfc7b25, 4);      // SHA-256_Update(salt)
FUN_00003e20(output, ctx);              // SHA-256_Final → 32-byte hash
```

**Storage location:** Secure NVRAM via `B7A777D1-6EB6-469E-AD1F-1165EB92B3FF` protocol
- Slot table: up to 16 password slots (indexed 0-15)
- Cmd `0x10..0x1f` = credential identifier for each slot (20 bytes)
- Cmd `0x20..0x2f` = BIOS/Admin password hash for each slot (32 bytes)
- Cmd `0x30..0x3f` = HDD password hash for each slot (32 bytes)
- B7A777D1 protocol interface: `proto->Cmd(proto, cmd, cred_GUID, &size, buf)`

### ⚠️ CRITICAL: Stored hash is XOR-obfuscated (FUN_0000149c)

The hash bytes are **NOT** stored as raw SHA-256 output. They are XOR-obfuscated with a 20-byte key derived from service tag data:

```c
// Applied before write and after read (symmetric XOR)
for (i = 1; i < hash_size; i++)   // NOTE: byte 0 is NOT XOR'd
    stored_hash[i] ^= derive_key[i % 20];
```

**Key derivation (FUN_0000149c):**
1. Read 24-byte service data from B7A777D1 cmd `0x2618` (service tag)
2. Copy 16 bytes from DAT_0000a4d0 (fixed key material in PE_0463 .data)
3. Call secondary protocol `DAT_0000afc8` with service data → 20-byte XOR key
4. XOR key is cycled: `key[i % 20]` for bytes 1..31

**Implications for NVRAM analysis:**
- Raw NVRAM bytes ≠ SHA256(password + salt)
- To verify a password against NVRAM, must first XOR-decode with derive_key
- derive_key requires: service tag (from cmd 0x2618) + DAT_0000a4d0 salt + DAT_0000afc8 protocol
- Byte index 0 of stored hash is unobfuscated (can be used to verify decryption)
- The `DAT_0000afc8` protocol identity is still unknown — needs further analysis

---

## 7b. Dell 8FC8 Challenge/Response Algorithm (CONFIRMED)

**Purpose:** Recovery bypass for forgotten BIOS password

**Challenge format:** `{7-char service tag}-{4-char code}`
- Service tag obtained via protocol cmd `0x2618`
- 4-char code = `FUN_00004a5c(service_tag_code, 4)` encoded from `DAT_0000560c`

**Response verification:** PE_0463 `FUN_00001ea4` / `FUN_0000933c`

### CRITICAL CORRECTION: The hash function is MD5, NOT SHA-1

`FUN_00007df8` (previously misidentified as SHA-1) is an **obfuscated MD5** implementation:
- Only 4 state variables A/B/C/D (MD5) — SHA-1 requires 5
- Round rotation amounts `7,12,17,22 / 5,9,14,20 / 4,11,16,23 / 6,10,15,21` are the exact MD5 round schedule
- Output is 16 bytes (MD5=128 bits) — matches the 16 bytes consumed by the 8FC8 verifier
- Per-round K constants are XOR-obfuscated in `.data` with mask `0x6d2f93a5`
- Init values `0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476` happen to be identical for both MD5 and SHA-1 first 4 words — this was the source of confusion

**Algorithm (key=0xBF97 / `-0x4069`):**
```python
def compute_8fc8_response(service_tag_7chars):
    # Step 1: Build 23-byte input buffer
    buf = bytearray(23)
    buf[0:7] = sanitize(service_tag_7chars)       # Replace non-printable with '*'
    buf[7:11] = b'BF97'                            # Fixed 4-byte suffix (DAT_0000abb8)
    buf[11:19] = encode_5bit(service_tag_7chars)  # 8-byte 5-bit extraction of service tag
    # buf[19:23] = zeros (already zeroed)

    # Step 2: MD5(buf)  ← CORRECTED from SHA-1
    md5_hash = MD5(buf)  # 16 bytes

    # Step 3: Map all 16 bytes through lookup table (mod 72)
    TABLE = "0Q2drGk99rkQFMxN[Z5y3DGr16h638myIL2rzz2pzcU7JWLJ1EGnqRN4seZPRM2aBXIjbkGZ"
    response = ''.join(TABLE[b % 72] for b in md5_hash)
    return response  # 16-char response code
```

**MD5 obfuscation details (FUN_00004db8):**
- Two loop paths controlled by `DAT_0000a270` / `DAT_0000a268` iteration counts
- Round order is permuted between the two loops (1→2→3→4 vs 3→4→1→2)
- K-table constants stored in `.data` section XORed with `0x6d2f93a5` to obscure them
- Round function pointers passed as `param_3..param_7` (F,G,H,I functions for 4 rounds)

**Key validation (FUN_00008070):**
- Lookup table at `DAT_0000a9c0`, stride 0x18
- Starts with key `0x8FC8` (-0x7038)
- Returns 0xff if key NOT in table → keys 0xBF97/0x6FF1/0x1F66/0x1D3B return 0xff
- Keys in the table (0x8FC8 and others) are dispatched to `FUN_00008e78` instead

**5-bit encoding (FUN_00007e54) — COMPLETE:**

Takes first 5 bytes of service tag, extracts 8 five-bit values, then XOR-maps each through the lookup table:
```python
def encode_5bit(service_tag, key=0xBF97):
    s = bytearray(service_tag[:7])  # sanitize first
    # Save first 5 bytes at offsets 8-12 (working buffer)
    b0,b1,b2,b3,b4 = s[0],s[1],s[2],s[3],s[4]
    # Extract 8 five-bit values from b0..b4 (40 bits → 8×5 bits)
    v = [0]*8
    v[0] = b4 & 0x1f
    v[1] = ((b3 << 3 | b3 >> 5) & 0x11) | (b4 >> 5)
    v[2] = (b3 >> 2) & 0x1f
    v[3] = ((b2 & 0x0f) << 1) | (b3 >> 7)
    v[4] = ((b1 & 0x01) << 4) | (b2 >> 4)
    v[5] = (b1 >> 1) & 0x1f
    v[6] = ((b0 & 0x07) << 2) | (b1 >> 6)
    v[7] = b0 >> 3
    # For each 5-bit value: XOR mix of the 5 source bytes, then table lookup
    out = []
    for vi in v:
        acc = 0xaa
        if vi & 0x01: acc ^= b4
        if vi & 0x02: acc ^= b3
        if vi & 0x04: acc ^= b2
        if vi & 0x08: acc ^= b1
        if vi & 0x10: acc ^= b0
        out.append(TABLE[acc % 72])
    return bytes(out)  # 8 output bytes
```

**Sanitize (FUN_000094e8):** Replace any byte outside ASCII `'!'` (0x21) to `'~'` (0x7e) with `'*'` (0x2a).

### Two-Tier Challenge/Response Architecture

**Path A — Secondary keys (NOT in lookup table, lVar2==0xff from FUN_00008070):**
- Keys: 0xBF97, 0x6FF1, 0x1F66, 0x1D3B
- Hash: MD5 only (FUN_00007df8)
- Input: 23-byte buffer (7-char tag + 4-char key hex + 8-char 5-bit-encoded tag)
- Output: 16 bytes → each byte mapped through `TABLE[byte % 72]` → 16-char response

**Path B — Primary keys (IN lookup table, dispatched via FUN_00008e78/FUN_00008fc4):**
- Keys: 0x8FC8 and others in DAT_0000a9c0 table
- Hash: MD5 (FUN_00008160 with table-configured variant) → SHA-256 (FUN_000080a8)
- Input: 11 bytes from challenge input + 4-byte key hex code = 15 bytes → MD5 → SHA-256
- Output: 32 SHA-256 bytes → position-dependent encoding in FUN_00008d20:
  `out[i] = TABLE[(sha256[i] + sha256[i+0x10]) % 72]` (mixing byte with byte 16 positions later)

**Key codec (FUN_00009504):** Converts key code to 4-char uppercase hex string (e.g., `0x8FC8` → `"8FC8"`)

**Key validation table (DAT_0000a9c0, stride=0x18) — COMPLETE:**
- Entry[0]: key `0x8FC8` (-0x7038) — the main Dell BIOS recovery code
- Entry[1]: key `0xE7A8` (-0x1858) — second primary code (TPM-linked path)
- Entry[2]: key `0xFFFF` (-0x0001) — terminator (loop exits when sVar1 == -1)
- Entry[i]: `offset+0` = key code (short), `offset+0x08` = variant function ptr, `offset+0x10` = table ptr
- `DAT_0000a778 = 0000E7A8...` encodes the `0xE7A8` key; `FUN_000094b4` checks if it's registered (TPM path selector)

**Lookup tables (72 chars each, located in .data):**
| Key    | Address    | Table (72 chars) |
|--------|------------|-----------------|
| 0xBF97 | DAT_0000ab50 | `0Q2drGk99rkQFMxN[Z5y3DGr16h638myIL2rzz2pzcU7JWLJ1EGnqRN4seZPRM2aBXIjbkGZ` |
| 0x6FF1 | DAT_0000ab00 | `08rptBxfbGVMz38IiSoeb360MKcLf4QtBCbWVzmH5wmZUcRR5DZG2xNCEv1nFtzsZB2bw1X0` |
| 0x1F66 | DAT_0000aab0 | `0ewr3d4xtUG1ku0BfIp7VFb21OTSno7KDLZYqsJWa6HMgCQR94m65y9Nl5Pvc8AjihE3X2z0` |
| 0x1D3B | DAT_0000aa60 | `0BfIUG1kuPvc8A9Nl5DLZYSno7Ka6HMgqsJWm65yCQR94b21OTp7VFX2z0jihE33d4xtrew0` |
| default | DAT_0000aa10 | `012345679abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0` |

---

## 8. Key Protocol/GUID Inventory (Complete)

### PE_0463 Internal GUID Table (from binary at raw 0x9040+)

| RVA | GUID | Role in PE_0463 |
|-----|------|-----------------|
| `a440` | `0AE3E2CF-13DD-4D97-BD5A-98FE0F14AFE6` | Unknown (located via aee8+0x140) |
| `a450` | `07D51D0D-7B3B-4C5C-B9EF-9DD70C0A489F` | Unknown (accessed in FUN_000019bc) |
| `a460` | `417ACEE0-6FA9-4A82-99D7-F9B1DD271E48` | Unknown (DAT_0000a440 protocol context) |
| `a470` | `7CE88FB3-4BD7-4679-87A8-A8D8DEE50D2B` | Handle registration GUID |
| `a480` | `773779CA-2AE8-4073-8BC5-43376A61BFD5` | Unknown (located in FUN_000019bc) |
| `a490` | `BD6B3090-6936-4DF0-BC73-68B06FB4E791` | Unknown (located in FUN_000019bc) |
| `a4c0` | `B7A777D1-6EB6-469E-AD1F-1165EB92B3FF` | **Secure NVRAM protocol** (DAT_0000aec0) |
| `a4d0` | `3A441BF0-D8E2-429E-B508-7054E3CA0FE6` | **Self GUID** — 16 bytes used as key material in XOR derivation (FUN_0000149c) |
| `a4e0` | `51AF821C-ADAF-4ABC-9FBF-26CD5245BA22` | NVRAM key config protocol (DAT_0000afd0) |
| `a4f0` | `60EED930-4789-40C3-ADFE-0B12317B56B1` | **Key derivation protocol** (DAT_0000afc8) — generates 20-byte XOR key |
| `a500` | `BB52D484-DC3F-4A1F-B86A-58FA9245270A` | Admin password entry GUID |
| `a510` | `7CEC093D-6BAC-420D-845C-CA1716AC5A92` | Owner password entry GUID |
| `a520` | `FEE3193F-CED3-4792-B804-A8F2B6241009` | HDD password entry GUID |
| `a530` | `38C1B06E-BDCA-45CD-B6E8-BF45845671FA` | BIOS/Admin password type identifier |
| `a540` | `4DDB3FAC-C556-4E26-AD8E-DC8758426889` | HDD password type identifier |
| `a550` | `C065AEAB-DD1C-4D49-BD33-4578E106C700` | Unknown password type ID |
| `a560` | `4D624984-D1CC-4C7C-BFE4-4D7F013FF25A` | Fixed 16-byte buffer for TPM variant |
| `a570` | `67B1372A-7ADE-4A47-8173-CC2B90D79D6C` | Unknown |
| `a580` | `F2C68B35-9114-4528-AC75-5ADF2EBD6DAB` | Key identifier for stored password |
| `a5a0` | `7310E28E-96EA-4360-946E-5ADC6BE8F531` | **TPM protocol** (DAT_0000afc0) |
| `a590` | `9EE41A8C-C112-4E4F-B2F0-65D0F9B133DB` | TPM capability protocol |
| `a5b0` | `F4CCBFB7-F6E0-47FD-9DD4-10A8F150C191` | SMM protocol GUID |
| `a5c0` | `C2702B74-800C-4131-8746-8FB5B89CE4AC` | Unknown (located at startup) |
| `a808` | `6E978D37-C32E-43B6-8CEB-CC9AA215109E` | **Credential GUID** — passed to all B7A777D1 NVRAM calls |

### Protocol/Module Registry

| GUID | Name | Module | Role |
|------|------|--------|------|
| `EE4E5898-3914-4259-9D6E-DC7BD79403CF` | AMI TSE | PE_0119 | BIOS auth UI / DXE driver |
| `D95D6B4F-92FA-4E78-9C48-C68C0813688E` | SMI Dispatcher | PE_0255 | SMI 0xAF handler |
| `F317B29B-7DC9-4114-9086-D7137EF4F118` | Setup PW State | PE_0290 | Manages Setup var pw flag |
| `3A441BF0-D8E2-429E-B508-7054E3CA0FE6` | Crypto Keystore | PE_0463 | SHA-256/MD5 hash, 8FC8 challenge |
| `B8CAA50A-5D0E-4AEB-819D-86CA29AC6A48` | BIOS PW Handler | PE_0516 | Password verify callback |
| `0AB697CE-B920-48AC-A265-EC5624EDCDD7` | PwHandlerProto | multiple | Password operation dispatch |
| `BB52D484-DC3F-4A1F-B86A-58FA9245270A` | Admin PW Entry | PE_0516 | Admin password credential ID |
| `7CEC093D-6BAC-420D-845C-CA1716AC5A92` | Owner PW Entry | PE_0516 | Owner password credential ID |
| `FEE3193F-CED3-4792-B804-A8F2B6241009` | HDD PW Entry | PE_0516 | HDD password credential ID |
| `C8BD7E42-AE85-408C-8ADA-177EE2C86DE9` | LinkDellPwData | PE_0119 | DXE↔SMM comm channel |
| `B7A777D1-6EB6-469E-AD1F-1165EB92B3FF` | Secure NVRAM | PE_0463 | Underlying password storage |
| `60EED930-4789-40C3-ADFE-0B12317B56B1` | Key Derive Proto | unknown | XOR key derivation (afc8) |
| `7310E28E-96EA-4360-946E-5ADC6BE8F531` | TPM Protocol | PE_0463 | TPM-backed challenge (afc0) |
| `6E978D37-C32E-43B6-8CEB-CC9AA215109E` | Credential GUID | PE_0463 | Credential slot identifier |
| `38C1B06E-BDCA-45CD-B6E8-BF45845671FA` | BIOS PW Type | PE_0463 | Identifies BIOS/Admin hash slot |
| `4DDB3FAC-C556-4E26-AD8E-DC8758426889` | HDD PW Type | PE_0463 | Identifies HDD hash slot |
| `EC87D643-EBA4-4BB5-A1E5-3F3E36B20DA9` | AMI Setup | multiple | 6141-byte setup blob |
| `18A3C6DC-5EEA-48C8-A1C1-B53389F98999` | SmmSwDispatch2 | PE_0255 | SMI registration |

---

## 9. Attack Surface (NVRAM Tampering)

**Target:** AMI Setup variable at GUID `EC87D643-EBA4-4BB5-A1E5-3F3E36B20DA9`

**Method via CVE-2021-21551 (`dbutil_2_3.sys`):**
1. Load `dbutil_2_3.sys` (BYOVD)
2. Use IOCTL `0x9B0C1EC8` (memmove) for arbitrary kernel r/w
3. Map NVRAM via `EFI_RUNTIME_SERVICES->GetVariable` / `SetVariable` calls from kernel
4. Write 0x00 to offset 0x359 in the "Setup" blob → clear password flag
5. Write back via `SetVariable` with auth attributes

**Limitation:** NvLock protection may prevent runtime NVRAM modification of authenticated variables. The variable may require physical presence or SMM-level auth to modify.

---

## 8. SMM Resident Handler (NOT YET FOUND)

The actual password hash storage and comparison logic is likely in an SMM-resident handler. SMM code runs in a protected memory region (SMRAM) and handles:
- Password hash verification
- Authenticated variable writes
- SMI-based NVRAM locking

**Candidates to investigate:**
- Additional SMM modules in volumes not yet fully analyzed
- PE_0072 SMI handler at `FUN_00001d84` / callback `FUN_00002ba8`
- Any module at `0x30000` address range (typical SMRAM base)

---

## 9. Next Steps

1. **[IN PROGRESS]** Deep RE of PE_0119 (AMI TSE) — password authentication flow
2. **[PENDING]** Trace DellPassword variable format (hash algorithm, structure)
3. **[PENDING]** Find SMM-resident password hash comparison (search for SHA-256 context, 32-byte buffers + CompareMem)
4. **[PENDING]** Analyze PE_0309 `FUN_*` that contains "Passwords do not match." to locate comparison path
5. **[PENDING]** Map full call chain: AMI TSE → DellPassword → hash comparison → SMM

---

## 10. Tool Chain

- **Extraction:** `platomav/BIOSUtilities` (DellPfsExtract) → UEFITool NE A73 (UEFIExtract)
- **Analysis:** Ghidra 12.0.4 headless with custom Java post-scripts
- **Scripts:** `ExportFunctionInfoScript.java` (batch scan), `DeepREScript.java` (decompile + GUID scan), `XRefPasswordScript.java` (cross-reference tracing)
- **Key fix:** Ghidra 12 API uses `decompileCompleted()` not `decompilationCompleted()`
