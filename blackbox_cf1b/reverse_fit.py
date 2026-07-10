"""CF1B reverse-engineering harness (consistency-driven fit from known pairs).

CF1B is an undocumented Dell service-tag suffix whose derivation runs inside the
machine's embedded controller (EC); the firmware payload is AES-encrypted, so
there is no binary to reverse. The only signal is confirmed (system-number ->
password) pairs. This module fits the algorithm to those pairs.

Method: for a hypothesised (hash / block-encoder, input construction, output map,
table length L) we can COMPUTE the pre-table bytes for every known tag, which
makes the unknown output table a byproduct -- each output position teaches one
(index -> char) entry. The CORRECT hypothesis is the one whose induced index->char
map is self-consistent across all samples with the MOST resolved collisions. A
wrong hypothesis collides with disagreeing chars and is rejected.

With only 2 pairs the discriminating signal is weak (~7 expected collisions at a
~71-char table); `best_fit` reports the ceiling so callers can see whether the
data is sufficient. A hypothesis is only declared SOLVED when it clears
`REAL_THRESHOLD` resolved collisions with zero contradictions.

Usage:
    python3 reverse_fit.py cf1b_pairs.json
    from reverse_fit import best_fit, load_pairs
"""
from __future__ import annotations
import hashlib
import json
import sys

import reference_dell as R
from reference_dell import (_byte_array_to_int, _int_array_to_byte, ENCODERS,
                            Tag6FF1Encoder, encscans, rol, rotationTable)

M = 0xFFFFFFFF

# A hypothesis needs many mutually-consistent collisions to be believable. At a
# ~71-entry table two pairs (32 samples) yield ~7 collisions for the true model;
# noise tops out ~3. Require a clear margin above noise.
REAL_THRESHOLD = 6


# --------------------------------------------------------------------------- #
#  pair loading
# --------------------------------------------------------------------------- #
def load_pairs(path):
    with open(path) as fh:
        data = json.load(fh)
    pairs = []
    for row in data["pairs"]:
        sysno = row["system_number"].upper()
        pw = row["password"]
        pairs.append((sysno, pw))
    return pairs


def _split(sysno):
    return sysno[:7].upper(), sysno[7:11].upper()


# --------------------------------------------------------------------------- #
#  consistency test
# --------------------------------------------------------------------------- #
def consistency(idxs_per_pair, chars_per_pair):
    """Return (index->char table, resolved_collisions) or (None, 0) on contradiction."""
    table = {}
    collisions = 0
    for idxs, chars in zip(idxs_per_pair, chars_per_pair):
        for k, ch in zip(idxs, chars):
            if k in table:
                collisions += 1
                if table[k] != ch:
                    return None, 0
            else:
                table[k] = ch
    return table, collisions


# --------------------------------------------------------------------------- #
#  search space 1: standard hashes (generatable without the circular table)
# --------------------------------------------------------------------------- #
_HASHES = {
    "sha256": lambda b: hashlib.sha256(b).digest(),
    "md5": lambda b: hashlib.md5(b).digest(),
    "sha1": lambda b: hashlib.sha1(b).digest(),
    "sha512": lambda b: hashlib.sha512(b).digest(),
    "sha224": lambda b: hashlib.sha224(b).digest(),
}


def _pad24(bs):
    b = bytearray(bs)
    b.append(0x80)
    while len(b) < 24:
        b.append(0)
    return bytes(b[:24])


def _constructions(tag, suf):
    base = {
        "tag+suf": tag + suf, "suf+tag": suf + tag, "tag": tag,
        "tag-suf": tag + "-" + suf, "tag+suf+tag": tag + suf + tag,
    }
    out = {}
    for n, s in base.items():
        e = s.encode("latin-1")
        out[n + ":raw"] = e
        out[n + ":24"] = _pad24(e)
    return out


def _maps(d, L):
    n = len(d)
    m = {f"o[i]%{L}": [d[i] % L for i in range(16)]}
    if n >= 32:
        m[f"(o[i]+o[i+16])%{L}"] = [(d[i] + d[i + 16]) % L for i in range(16)]
        m[f"o[i+16]%{L}"] = [d[i + 16] % L for i in range(16)]
        m[f"(o[i]^o[i+16])%{L}"] = [(d[i] ^ d[i + 16]) % L for i in range(16)]
    if n >= 32:
        m[f"(o[2i]+o[2i+1])%{L}"] = [(d[2 * i] + d[2 * i + 1]) % L for i in range(16)]
    return m


def standard_hash_search(pairs, min_coll=4):
    chars = [pw for _, pw in pairs]
    hits = []
    ceiling = 0
    sample_tag, sample_suf = _split(pairs[0][0])
    for cname in _constructions(sample_tag, sample_suf):
        for hname, hfn in _HASHES.items():
            digs = []
            for sysno, _ in pairs:
                tag, suf = _split(sysno)
                digs.append(hfn(_constructions(tag, suf)[cname]))
            for L in range(20, 96):
                for mname in _maps(digs[0], L):
                    idxs = [_maps(d, L)[mname] for d in digs]
                    tab, coll = consistency(idxs, chars)
                    if tab is not None:
                        ceiling = max(ceiling, coll)
                        if coll >= min_coll:
                            hits.append({
                                "kind": "hash", "hash": hname, "construction": cname,
                                "map": mname, "L": L, "collisions": coll, "table": tab,
                            })
    return hits, ceiling


# --------------------------------------------------------------------------- #
#  search space 2: Dell block-encoder family + 6FF1-style structural variants
#  (assumes CF1B's calculate_suffix uses the deterministic encscans table)
# --------------------------------------------------------------------------- #
def _calc_suffix_encscans(serial):
    arr2 = [4, 3, 2]
    suf = [0] * 8
    suf[0] = serial[4]
    suf[1] = (serial[4] >> 5) | (((serial[3] >> 5) | (serial[3] << 3)) & 0xF1)
    suf[2] = serial[3] >> 2
    suf[3] = (serial[3] >> 7) | (serial[2] << 1)
    suf[4] = (serial[2] >> 4) | (serial[1] << 4)
    suf[5] = serial[1] >> 1
    suf[6] = (serial[1] >> 6) | (serial[0] << 2)
    suf[7] = serial[0] >> 3
    suf = [v & 0xFF for v in suf]
    out = []
    for i in range(8):
        r = 0xAA
        if suf[i] & 1:  r ^= serial[arr2[0]]
        if suf[i] & 2:  r ^= serial[arr2[1]]
        if suf[i] & 4:  r ^= serial[arr2[2]]
        if suf[i] & 8:  r ^= serial[1]
        if suf[i] & 16: r ^= serial[0]
        out.append(encscans[r % len(encscans)])
    return out


def _build_block(serial, tag_str="CF1B"):
    arr = [ord(c) & 0xFF for c in (serial + tag_str)]
    arr = arr + _calc_suffix_encscans(arr)
    cnt = 23
    while len(arr) <= cnt:
        arr.append(0)
    arr[cnt] = 0x80
    block = _byte_array_to_int(arr)
    block[14] = cnt << 3
    return block


def _make_6ff1(c1, c2):
    def make_encode(self):
        for j in range(c1):
            self.A = (self.A | 0xA08097) & M
            self.B = (self.B ^ 0xA010908) & M
            self.C = (self.C | ((0x60606161 - j) & M)) & M
            self.D = (self.D ^ ((0x50501010 + j) & M)) & M
            for i in range(64):
                q = i >> 4
                k = (i & 15) - ((i & 12) << 1) + 12
                if q == 0:   t = self.calculate(self.f2, i & 15, i + 32)
                elif q == 1: t = self.calculate(self.f3, (i * 5 + 1) & 15, (i & 15))
                elif q == 2: t = self.calculate(self.f4, (i * 3 + 5) & 15, k + 16)
                else:        t = self.calculate(self.f5, (i * 7) & 15, k + 48)
                self.A, self.D, self.C = self.D, self.C, self.B
                self.B = (rol(t, rotationTable[q][i & 3]) + self.B) & M
            self.increment_data()
        for j in range(c2):
            self.A = (self.A | 0x100097) & M
            self.B = (self.B ^ 0xA0008) & M
            self.C = (self.C | ((0x50501010 - j) & M)) & M
            self.D = (self.D ^ ((0x60606161 + j) & M)) & M
            for i in range(64):
                q = i >> 4
                k = (i & 15) - ((i & 12) << 1) + 12
                if q == 0:   t = self.calculate(self.f4, ((i & 15) * 3 + 5) & 15, k + 16)
                elif q == 1: t = self.calculate(self.f5, ((i & 3) * 7 + (i & 12) + 4) & 15, (i & 15) + 32)
                elif q == 2: t = self.calculate(self.f2, k & 15, k)
                else:        t = self.calculate(self.f3, ((i & 15) * 5 + 1) & 15, (i & 15) + 48)
                g = (i >> 4) + 2
                self.A, self.D, self.C = self.D, self.C, self.B
                self.B = (rol(t, rotationTable[g & 3][i & 3]) + self.B) & M
            self.increment_data()
    return type(f"F{c1}_{c2}", (Tag6FF1Encoder,), {"make_encode": make_encode})


def block_family_search(pairs, cmax=32, min_coll=4):
    chars = [pw for _, pw in pairs]
    hits = []
    ceiling = 0
    encoders = {name: ENCODERS[name]
                for name in ("595B", "1D3B", "D35B", "1F66", "6FF1", "1F5A", "BF97")}
    for c1 in range(1, cmax + 1):
        for c2 in range(1, cmax + 1):
            encoders[f"6FF1({c1},{c2})"] = _make_6ff1(c1, c2)
    for ename, ecls in encoders.items():
        decoded = [_int_array_to_byte(ecls.encode(_build_block(_split(s)[0])))
                   for s, _ in pairs]
        for L in range(24, 96):
            idxs = [[d[i] % L for i in range(16)] for d in decoded]
            tab, coll = consistency(idxs, chars)
            if tab is not None:
                ceiling = max(ceiling, coll)
                if coll >= min_coll:
                    hits.append({
                        "kind": "block", "encoder": ename, "map": "d[i]%L",
                        "L": L, "collisions": coll, "table": tab,
                    })
    return hits, ceiling


# --------------------------------------------------------------------------- #
#  top-level fit
# --------------------------------------------------------------------------- #
def best_fit(pairs, cmax=24):
    """Run all searches. Return a dict describing the outcome."""
    h_hits, h_ceil = standard_hash_search(pairs, min_coll=1)
    b_hits, b_ceil = block_family_search(pairs, cmax=cmax, min_coll=1)
    all_hits = h_hits + b_hits
    all_hits.sort(key=lambda x: -x["collisions"])
    ceiling = max(h_ceil, b_ceil)
    best = all_hits[0] if all_hits else None
    solved = bool(best and best["collisions"] >= REAL_THRESHOLD)
    return {
        "n_pairs": len(pairs),
        "ceiling": ceiling,
        "threshold": REAL_THRESHOLD,
        "solved": solved,
        "best": best,
        "top": all_hits[:10],
    }


def generate_standard(hyp, sysno):
    """Generate a password from a SOLVED standard-hash hypothesis.

    Returns (password, unknown_positions). Positions whose table index was never
    observed in the training pairs are rendered as '?' -- never guessed.
    """
    assert hyp["kind"] == "hash"
    tag, suf = _split(sysno)
    data = _constructions(tag, suf)[hyp["construction"]]
    d = _HASHES[hyp["hash"]](data)
    L = hyp["L"]
    idxs = _maps(d, L)[hyp["map"]]
    table = hyp["table"]
    out = []
    unknown = []
    for i, k in enumerate(idxs):
        if k in table:
            out.append(table[k])
        else:
            out.append("?")
            unknown.append(i)
    return "".join(out), unknown


def _cli(argv):
    if len(argv) < 2:
        print("usage: reverse_fit.py <pairs.json>")
        return 2
    pairs = load_pairs(argv[1])
    res = best_fit(pairs)
    print(f"pairs: {res['n_pairs']}   ceiling(consistent collisions): {res['ceiling']}"
          f"   threshold: {res['threshold']}")
    if res["solved"]:
        print("\nSOLVED. Best hypothesis:")
        b = res["best"]
        print({k: v for k, v in b.items() if k != "table"})
    else:
        print("\nNOT SOLVED from current pairs. The best fits are indistinguishable "
              "from noise:")
        for h in res["top"][:6]:
            info = {k: v for k, v in h.items() if k != "table"}
            print("  ", info)
        print(f"\nNeed a hypothesis reaching >= {res['threshold']} consistent "
              f"collisions. Add more confirmed pairs to cf1b_pairs.json and re-run.")
    return 0


if __name__ == "__main__":
    raise SystemExit(_cli(sys.argv))
