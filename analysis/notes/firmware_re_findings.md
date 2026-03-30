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
- Slot table: up to 16 password slots
- Slot+0x10: credential identifier (20 bytes)
- Slot+0x20: SHA-256 hash (32 bytes)
- Slot+0x30: additional data

---

## 7b. Dell 8FC8 Challenge/Response Algorithm (CONFIRMED)

**Purpose:** Recovery bypass for forgotten BIOS password

**Challenge format:** `{7-char service tag}-{4-char code}`
- Service tag obtained via protocol cmd `0x2618`
- 4-char code = `FUN_00004a5c(service_tag_code, 4)` encoded from `DAT_0000560c`

**Response verification:** PE_0463 `FUN_00001ea4` / `FUN_0000933c`

**Algorithm (key=0xBF97 / `-0x4069`):**
```python
def compute_8fc8_response(service_tag_7chars):
    # Step 1: Build 23-byte input buffer
    buf = bytearray(23)
    buf[0:7] = sanitize(service_tag_7chars)       # Replace non-printable with '*'
    buf[7:11] = b'BF97'                            # Fixed 4-byte suffix (DAT_0000abb8)
    buf[11:19] = encode_5bit(service_tag_7chars)  # 8-byte 5-bit extraction of service tag

    # Step 2: SHA-1(buf)
    sha1_hash = SHA1(buf)  # 20 bytes

    # Step 3: Map first 16 bytes through lookup table (mod 72)
    TABLE = "0Q2drGk99rkQFMxN[Z5y3DGr16h638myIL2rzz2pzcU7JWLJ1EGnqRN4seZPRM2aBXIjbkGZ"
    response = ''.join(TABLE[b % 72] for b in sha1_hash[:16])
    return response  # 16-char response code
```

**5-bit encoding (FUN_00007e54):**
Extracts 8 groups of 5 bits from 7-byte service tag via bit manipulation, then XOR-combines with 5-bit masks.

**Alternative lookup tables by key:**
| Key    | Table (72 chars) |
|--------|-----------------|
| 0xBF97 | `0Q2drGk99rkQFMxN[Z5y3DGr16h638myIL2rzz2pzcU7JWLJ1EGnqRN4seZPRM2aBXIjbkGZ` |
| 0x6FF1 | `08rptBxfbGVMz38IiSoeb360MKcLf4QtBCbWVzmH5wmZUcRR5DZG2xNCEv1nFtzsZB2bw1X0` |
| 0x1F66 | `0ewr3d4xtUG1ku0BfIp7VFb21OTSno7KDLZYqsJWa6HMgCQR94m65y9Nl5Pvc8AjihE3X2z0` |
| 0x1D3B | `0BfIUG1kuPvc8A9Nl5DLZYSno7Ka6HMgqsJWm65yCQR94b21OTp7VFX2z0jihE33d4xtrew0` |
| default | `012345679abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0` |

---

## 8. Key Protocol/GUID Inventory (Complete)

| GUID | Name | Module | Role |
|------|------|--------|------|
| `EE4E5898-3914-4259-9D6E-DC7BD79403CF` | AMI TSE | PE_0119 | BIOS auth UI / DXE driver |
| `D95D6B4F-92FA-4E78-9C48-C68C0813688E` | SMI Dispatcher | PE_0255 | SMI 0xAF handler |
| `F317B29B-7DC9-4114-9086-D7137EF4F118` | Setup PW State | PE_0290 | Manages Setup var pw flag |
| `3A441BF0-D8E2-429E-B508-7054E3CA0FE6` | Crypto Keystore | PE_0463 | SHA-256 hash store/compare |
| `B8CAA50A-5D0E-4AEB-819D-86CA29AC6A48` | BIOS PW Handler | PE_0516 | Password verify callback |
| `0AB697CE-B920-48AC-A265-EC5624EDCDD7` | PwHandlerProto | multiple | Password operation dispatch |
| `BC8F69B5-E43B-4D23-B2DF-B969301909F2` | BIOS Password | PE_0463 | BIOS admin/system pw GUID |
| `08D22BDB-9E2F-4E18-A71A-6BC5A5509FD9` | HDD Password | PE_0463 | HDD password GUID |
| `C8BD7E42-AE85-408C-8ADA-177EE2C86DE9` | LinkDellPwData | PE_0119 | DXE↔SMM comm channel |
| `B7A777D1-6EB6-469E-AD1F-1165EB92B3FF` | Secure NVRAM | PE_0463 | Underlying password storage |
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
