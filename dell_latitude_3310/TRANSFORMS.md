# Latitude 3310 EC — hash / crypto / transform functions

Follow-up to `CRYPTO_ENCODING.md`: which **code functions** take input and hash /
transform it, and how they relate to the base‑N digit tables that render a
16‑char output.

Function bodies in these regions do **not** decompile cleanly (the community
ARCompact SLEIGH module lacks several opcodes — exactly the rotate/multiply ops
hashing relies on, shown as `asm_instruction_*` / `halt_unimplemented`). But the
**call graph is reliable** (objdump decodes `bl`/`jl` targets correctly), and the
constant tables are byte‑exact, so the *identification* and *structure* below are
solid even though the exact arithmetic isn't readable from this toolchain.

## Hash / crypto engines (functions that transform input)

### SHA‑256 engine  — around `0xBFD08000‑0xBFD08600` (K‑table at `0xBFD084B0`)
```
0xBFD0A698                          application entry
  └─ 0xBFD09820
       └─ 0xBFD08A3C                SHA-256 driver (context lifecycle)
            ├─ 0xBFD07C3C           \
            ├─ 0xBFD07C7C            |  block / update / pad / finalize
            ├─ 0xBFD07CB4            |  primitives (0xBFD07D18 uses the
            ├─ 0xBFD07D18            |  rotate-class opcode the module can't model)
            ├─ 0xBFD089B8            |
            └─ 0xBFD08C08           /
0xBFD09184                          second SHA driver (self-recursive block loop)
0xBFD090E6 / 0xBFD080D8             SHA helper / init
```

### CRC‑32 engine — around `0xBFCFA000‑0xBFCFB000` (table at `0xBFCFAD7C`)
```
0xBFCFED90
  └─ 0xBFCFDFA0
0xBFCFD134                          CRC top-level (fan-in 2)
  └─ 0xBFCFC2D4
       └─ 0xBFCFBA30                CRC orchestrator — calls 7 CRC primitives:
            0xBFCFAC0C 0xBFCFACB4 0xBFCFADE0 0xBFCFAEB8
            0xBFCFAECC 0xBFCFAF6C 0xBFCFAF90
0xBFCFA4B0                          table-driven CRC update (calls 0xBFCFA7C8/AA58/AB8C)
```

### SDSA signature verification
`VerifyEcSdsaSignature` (string @ `0xBFD04DC8`, "used %d ms") — hashes an image
(SHA‑256 above) and verifies a Dell "Secure Digital Signature Algorithm" signature;
the public‑key step is most likely offloaded to the MEC hardware PKE (no software
big‑integer loop is present in the recovered code).

## The 16‑char encoder

The digit tables (`0xBFD12D6C` lowercase base‑35, `0xBFD12D8F` uppercase base‑36)
are consumed by the number/string formatter subtree:
```
0xBFD12B32  (formatter)
  └─ 0xBFD12CD4
       └─ 0xBFD12D28   digit emitter — immediately precedes the tables at 0xBFD12D6C
```
No `bl` caller resolves to `0xBFD12B32` — it is reached through the printf‑style
vararg dispatch, consistent with a general `%d/%x`‑class formatter.

## How they connect (the transform pipeline)

No single function calls both a hash engine **and** the encoder — they are
**decoupled**, which is the normal C shape:

```
   input  ──►  SHA‑256 / CRC‑32 engine  ──►  value/digest  ──►  base‑N formatter (0xBFD12B32)  ──►  16‑char string
             (0xBFD08A3C / 0xBFCFBA30)                          (uses tables @ 0xBFD12D6C)
```

i.e. the application layer computes a digest, then renders it to the 16‑char code
via the digit tables — like `hash(x)` followed by `sprintf(buf,"%…",digest)`.

## What is NOT present
No AES S‑box/inverse S‑box, no SHA‑1 (no `0xC3D2E1F0` / round constants), no MD5
(no `T[]`), no RC4/DES fingerprints. Crypto surface = **SHA‑256 + CRC‑32 + SDSA verify**.

## To fully resolve the exact 16‑char algorithm
The encoder body and the hash math are in the mis‑decoding regions. Cracking the
exact scheme needs one of: the **MEC part number + datasheet** (to map the
`0xFFFFF8xx` hardware register block and confirm any HW hash/PKE), a **more
complete ARC decompiler / manual decode** of the ~1 KB `0xBFD12Bxx` formatter and
the SHA primitives, or **dynamic tracing** of the EC.
