# Dell service-tag BIOS master-password generator + CF1B recovery harness

Recovers the 16-char BIOS master password for a locked Dell prompt that shows a
`System Number: TAG-SUFFIX` (7-char service tag + 4-char suffix) and accepts the
answer via **Ctrl+Enter**. For owners recovering access to their own hardware.

```
python3 dell_cf1b.py 1234567-1F5A     # -> 2ls2b8GiP9H032kx
python3 dell_cf1b.py ABCDEFG-BF97      # -> kr9Z1cmPpahGzsQ[
python3 dell_cf1b.py JY5M453-CF1B      # -> status (CF1B is unsolved; see below)
python3 dell_cf1b.py --list
python3 tests/test_vectors.py          # 3/3
```

## What works

| Component | Status |
|---|---|
| `reference_dell.py` | Byte-exact port of the bacher09 Dell family. **30/30** published service-tag vectors. |
| Solvable suffixes | `595B D35B 2A7B A95B 1D3B 1F66 6FF1 1F5A BF97 E7A8` — generated directly, verified. |
| `reverse_fit.py` | Consistency-driven fitting harness for the undocumented **CF1B**. |
| CF1B | **Unsolved** from the two confirmed pairs (see below). |

## How each documented suffix is computed

`serial(7) + suffix(4)` → append 8 `calculate_suffix` bytes → pad to 24 (`0x80`
marker, bit-length in word 14) → a **suffix-specific modified-MD5 block encoder**
(`blockEncode`, differing per suffix in loop counts / magic constants / round
schedule) → 16 output bytes → `password[i] = TABLE_suffix[ out[i] % len(TABLE) ]`.
`E7A8` instead runs a custom pre-encode then a *real* SHA-256 and maps
`table[(d[i+16]+d[i]) % len]`, emitting two candidates.

## CF1B: why it isn't cracked yet, and how recovery would actually work

CF1B is **not** in any public reference, and you confirmed the two known passwords
unlock real hardware — so the algorithm is genuine but bespoke. It runs inside the
machine's **embedded controller (EC)**; the firmware payload is **AES-encrypted**,
so there is no binary to statically reverse. The only signal is confirmed
`(tag → password)` pairs.

We searched, against the two pairs:

- standard hashes (sha256/md5/sha1/sha512/sha224) × 30 input constructions × 5
  output maps × all table lengths — **ceiling 3 consistent collisions (noise)**;
- the full Dell block-encoder family + `6FF1`-style **two-parameter** structural
  variants (1024 of them) — **ceiling 3 (noise)**.

The true model would spike to ~7 consistent collisions. It never did: **CF1B is
not a loop-count/counter variant of any documented suffix.**

### The recoverability picture (answering "how do we get the table + variables?")

The output rule is `char[i] = TABLE[ preByte[i] % len(TABLE) ]`. Two facts govern
everything:

1. **The TABLE is only recoverable if you can compute `preByte`**, which requires
   knowing the encoder. And the encoder's output has full MD5 avalanche, so the
   `(tag → password)` mapping leaks nothing about the encoder's internal
   constants. That is the circular wall — and it's why 2 pairs (or 200 pairs) of
   pure I/O cannot, by themselves, reveal a from-scratch bespoke primitive.

Realistic avenues, best-first:

- **(A) Many pairs + a TARGETED structural search.** The family evolved in small
  steps (`6FF1`→`BF97` is a single counter change; `E7A8` reuses the same magic
  constants `0xA08097, 0xA010908, 0x60606161, 0x50501010, 0x100097, 0xA0008`).
  CF1B is almost certainly a *close relative*. Collect **many confirmed pairs**
  (start ~30–50) and expand the search over that specific, enumerable space of
  constants / round-function orderings (`f2..f5`, negative variants) / dual-loop
  schedules / `md5magic` vs `md5magic2`. With ~50 pairs the consistency test picks
  the right member out of thousands of candidates with essentially no false
  positives **and** recovers most of the 71-entry table at the same time. This is
  the path this harness is built to finish automatically — add pairs to
  `cf1b_pairs.json` and re-run `reverse_fit.py`.
- **(B) The table alphabet is guessable, the permutation is not.** The known Dell
  tables are 71 chars: a scrambled `0-9a-zA-Z` (leading/trailing `0`). CF1B's
  observed output chars are a subset of that alphabet; ~20 pairs would confirm the
  alphabet. But the *order* only becomes meaningful once (A) fixes the encoder.
- **(C) Differential probing of the oracle.** The working generator is itself an
  oracle. Feed tags that differ in one character and watch the output: full
  diffusion across all 16 positions confirms a real hash (rules out any
  substitution/linear shortcut). Useful as a diagnostic, not a break.
- **(D) EC side-channel (hardware).** Because the EC *computes* CF1B at runtime,
  the AES only protects the stored image, not the live computation. Power/timing
  analysis or fault injection on the EC while it hashes a known tag can leak the
  round constants directly. This is the standard way encrypted-firmware EC keygens
  are actually broken, but it needs physical access and equipment (glitcher / DPA
  rig).

If CF1B turns out to be a genuinely novel primitive (not an in-family MD5
variant), then (A) will not converge and only (D) — or obtaining the algorithm
from whoever derived it — will work. This tool never emits an unverified CF1B
password; it fits and generates only once the data pins the algorithm past
`REAL_THRESHOLD`.

## Files

- `reference_dell.py` — validated port of the Dell family (the oracle).
- `reverse_fit.py` — CF1B fitting harness (`best_fit`, searches, `generate_standard`).
- `dell_cf1b.py` — CLI.
- `cf1b_pairs.json` — confirmed CF1B ground-truth pairs (add more here).
- `tests/test_vectors.py` — port vectors + methodology proof + CF1B state.

Standard library only. The reference port is derived from the open-source
`bacher09/pwgen-for-bios` project for validation purposes.
