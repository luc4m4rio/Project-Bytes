# Dell 8FC8 keygen research

Reverse-engineering the Dell BIOS master-password algorithm for suffix `8FC8`
(observed on Latitude 5530 systems, service-tag suffix printed on the LCD when
you fail the admin password three times).

## Repo contents

| File | Purpose |
|---|---|
| `keygen.py` | Faithful Python port of the community Dell keygen framework: `Tag595B`, `TagD35B`, `Tag1D3B`, `Tag1F66`, `Tag6FF1`, `TagBF97`, `Tag1F5A`, `TagE7A8`, `TagE7A8Second` inner encoders, plus the `SEED_8FC8` alphabet extracted from `DellSecurityVaultSmm` at VA `0xA280` and the `state[j+16] + state[j] mod 72` formatter that the BIOS's `FUN_00008c50` uses. Includes `keygen_8FC8(tag)` — currently produces the E7A8-recipe answer, which does **not** match observed pairs. |
| `test_pairs.py` | Runs `keygen_8FC8` against 12 known `(tag → password)` pairs. |
| `search.py` | Grid search over inner-encoder × encBlock-packing × state-layout × seed-index combinations (13,312 cells). Documents the null result. |

## Known ground-truth pairs (all Latitude 5530, suffix 8FC8)

```
BC91NL3  ->  2XykI691322s03r4
H9ZLSL3  ->  JR0WnRPERzRQzNq[
8VRTSL3  ->  msffe422daw5jde4
9I87UL3  ->  mdgrr42PKq4hdr58
FVTLLS3  ->  4Zh8hMBcksLEBM19
8709FK3  ->  qnprBM2PP3rzLck2
1NXQU23  ->  1BGLGGUJUjxZj12G
5SR8TL3  ->  aUr[hhIRskszkpsM
31WYGS3  ->  JQMLk265rz3QIkQI
4GMSTL3  ->  sLkNM[BQ4L4Ixm34
RE4FSE3  ->  Lsp01Mq8zZ42GzI[
GHJTR23  ->  xzdkGyjz6E9k3522
```

Every password is 16 chars long and every character belongs to `SEED_8FC8`.

## What is confirmed

1. **Output alphabet.** `SEED_8FC8` at VA 0xA280 is the correct 72-character seed table. It is a permutation of the E7A8 alphabet.
2. **Formatter shape.** The BIOS `FUN_00008c50` applies `output[j] = SEED[(state[j] + state[j+16]) mod 72]` for `j ∈ [0, 16)` over a 32-byte `state` buffer.
3. **Framework family.** 8FC8 is in the "new family" table `DAT_0000a9c0` alongside E7A8, not the old bit-pack family.
4. **Not the plain E7A8 recipe.** The E7A8 recipe — `TagE7A8Encoder(pack_le(tag+"8FC8"))` → SHA-256 → seed map — produces valid-alphabet output but is wrong at every position for every one of the 12 pairs.
5. **Not a simple substitution in the framework.** Grid-searching 8 inner-encoder variants × 16 encBlock packings × 16 state layouts × 4 index combiners (13,312 cells) yielded zero hits.

## What is unknown / most likely explanation

Consistent with the previous static analysis of `FUN_00008da8`, which found that
the 8FC8 lookup-table entry has a **NULL key pointer** and therefore does *not*
reach the in-BIOS keyed-SHA path, the 32-byte `state` handed to `FUN_00008c50`
for 8FC8 is not produced in the SMM binary. It is produced by the embedded
controller (EC) via `vault.recv_data(32, local_40)`.

The most probable structure is:
- `state = HMAC-SHA256(K_ec, tag_bytes)` (or a similar keyed construction), where
  `K_ec` is a per-model constant burned into the EC firmware image.

To recover the algorithm, extract the EC firmware (SPI dump, or intercept from
a BIOS update image that contains an EC blob) and reverse the routine that
produces the 32 bytes returned to SMM. `K_ec` is almost certainly a fixed 16- or
32-byte constant literal in the EC's `.rodata`. Once `K_ec` is known, this
repo's framework is the target: swap `sha256(inner)` in `keygen_8FC8` for
`HMAC(K_ec, tag_bytes)` and re-run `test_pairs.py`; it should go 12/12 green.

## Immediate next steps

1. **Dump the EC.** For Latitude 5530 the EC is a Nuvoton/ITE. Recover the
   firmware via `flashrom`/`ch341a` on the EC SPI, or extract from a Dell BIOS
   update package (the `.exe` normally contains an EC section that PFS_Extract
   surfaces alongside the SystemBIOS blob).
2. **Locate the key.** In the extracted EC image, grep for the constants around
   the 32-byte `send` handler that responds to the BIOS's `vault` command. The
   32-byte state has to be constructed there; the key is either literal or
   XOR-scrambled with a short mask.
3. **Wire it into `keygen_8FC8`.** Replace the SHA-256 step with the discovered
   construction. The rest of the pipeline is already correct (verified by the
   fact that the output alphabet is right and only the values are wrong).

## Usage

```bash
python3 test_pairs.py           # currently 0/12 — placeholder framework
python3 keygen.py BC91NL3       # emit the two E7A8-recipe candidates
python3 search.py               # replay the 13,312-cell grid search
```
