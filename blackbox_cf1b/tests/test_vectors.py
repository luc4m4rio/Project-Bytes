"""Tests: (1) the port is byte-exact, (2) the fitting methodology actually works,
(3) CF1B's current state is honestly documented.

Runs under pytest, or standalone: `python3 tests/test_vectors.py`.
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, ROOT)

import reference_dell as R
import reverse_fit


# --------------------------------------------------------------------------- #
#  1. Byte-exact port vs published service-tag vectors
# --------------------------------------------------------------------------- #
SERVICE_TAG_VECTORS = [
    ("1234567", "595B", ["46rg65ky"]),
    ("1234567", "D35B", ["5tc8q9re"]),
    ("1234567", "2A7B", ["J1KuwWpSUgnDarfi"]),
    ("1234567", "A95B", ["46rg65ky"]),
    ("1234567", "1D3B", ["Sn4fkF8bS57NymZl"]),
    ("1234567", "1F66", ["kIpTBzx0m3s10JDR"]),
    ("1234567", "6FF1", ["Rzn1wGe555H5bM2r"]),
    ("OPENSRC", "1D3B", ["S3yJ91q0Gar3O72I"]),
    ("ABCDEFG", "1D3B", ["xvn0qEeftqyrkG52"]),
    ("7G9C0G2", "6FF1", ["35c0b0tVb32Z6ivD"]),
    ("DELLSUX", "1F66", ["qHXaL0ntli6Gu4c0"]),
    ("CRPP562", "1F66", ["8i5qLGa9woA919Ys"]),
    ("1234567", "1F5A", ["2ls2b8GiP9H032kx"]),
    ("OPENSRC", "1F5A", ["ZC3j2t56eIe4Thgi"]),
    ("ABCDEFG", "1F5A", ["x2zL5n7jj2Gl2TIh"]),
    ("1234567", "BF97", ["2r09GZhU[r0kW2zr"]),
    ("OPENSRC", "BF97", ["Dp29XkbyMrkBrp6Z"]),
    ("ABCDEFG", "BF97", ["kr9Z1cmPpahGzsQ["]),
    ("DELLSUX", "BF97", ["rrNM2LrbD8nGsd2P"]),
    ("1234567", "E7A8", ["Qk3LkU22kPeyq2jd", "rLIqjUy59IG2JU2R"]),
    ("D875TG2", "E7A8", ["rLZc96rMZyGQ2GMG", "1Q6rxIWMGUznXZNy"]),
]


def test_port_matches_published_vectors():
    for serial, tag, expected in SERVICE_TAG_VECTORS:
        got = R.keygen_dell(serial, tag, hdd=False)
        assert sorted(got) == sorted(expected), f"{serial}-{tag}: {got} != {expected}"


# --------------------------------------------------------------------------- #
#  helper: compute the real pre-table bytes for a documented suffix
# --------------------------------------------------------------------------- #
def _real_decoded(serial, tag):
    arr = [ord(c) & 0xFF for c in (serial + tag)]
    arr = arr + R.calculate_suffix(arr, tag, hdd=False)
    cnt = 23
    while len(arr) <= cnt:
        arr.append(0)
    arr[cnt] = 0x80
    block = R._byte_array_to_int(arr)
    block[14] = cnt << 3
    return R._int_array_to_byte(R.ENCODERS[tag].encode(block))


# --------------------------------------------------------------------------- #
#  2. Methodology: consistency SPIKES for the true model, stays noise for wrong
# --------------------------------------------------------------------------- #
_1F66_PAIRS = [
    ("1234567", "kIpTBzx0m3s10JDR"),
    ("DELLSUX", "qHXaL0ntli6Gu4c0"),
    ("CRPP562", "8i5qLGa9woA919Ys"),
    ("CDG8T32", "4Ke3y2L3kTP2f6Vo"),
    ("8M5RQ32", "3rlrbaSj46Iw221g"),
]


def test_consistency_recovers_true_model():
    chars = [pw for _, pw in _1F66_PAIRS]
    L = len(R.extraCharacters["1F66"])

    # TRUE encoder -> perfectly consistent, many resolved collisions, and the
    # recovered table reproduces every password.
    decoded_true = [_real_decoded(s, "1F66") for s, _ in _1F66_PAIRS]
    idxs_true = [[d[i] % L for i in range(16)] for d in decoded_true]
    table, coll = reverse_fit.consistency(idxs_true, chars)
    assert table is not None, "true model must be self-consistent"
    assert coll >= reverse_fit.REAL_THRESHOLD, f"true model collisions {coll} too low"
    for (serial, pw) in _1F66_PAIRS:
        d = _real_decoded(serial, "1F66")
        regen = "".join(table[d[i] % L] for i in range(16))
        assert regen == pw

    # WRONG encoder (6FF1 instead of 1F66) -> contradiction or far fewer collisions.
    decoded_wrong = [_real_decoded(s, "6FF1")[:16] for s, _ in _1F66_PAIRS]
    # feed the WRONG bytes but the 1F66 passwords: should not cleanly reproduce.
    idxs_wrong = [[d[i] % L for i in range(16)] for d in decoded_wrong]
    table_w, coll_w = reverse_fit.consistency(idxs_wrong, chars)
    assert table_w is None or coll_w < reverse_fit.REAL_THRESHOLD, \
        "wrong model should not pass the threshold"


# --------------------------------------------------------------------------- #
#  3. CF1B honest state: NOT solvable from the two confirmed pairs
# --------------------------------------------------------------------------- #
def test_cf1b_unsolved_from_two_pairs():
    pairs_file = os.path.join(ROOT, "cf1b_pairs.json")
    pairs = reverse_fit.load_pairs(pairs_file)
    assert len(pairs) >= 2
    res = reverse_fit.best_fit(pairs)
    # Documents reality: with only these pairs the best fit is noise-level.
    assert not res["solved"], (
        "CF1B unexpectedly 'solved' -- if you added many pairs and this fires, "
        "wire up generation and update this assertion."
    )
    assert res["ceiling"] < reverse_fit.REAL_THRESHOLD


if __name__ == "__main__":
    fns = [v for k, v in sorted(globals().items()) if k.startswith("test_")]
    failed = 0
    for fn in fns:
        try:
            fn()
            print(f"PASS  {fn.__name__}")
        except AssertionError as e:
            failed += 1
            print(f"FAIL  {fn.__name__}: {e}")
    print(f"\n{len(fns) - failed}/{len(fns)} passed")
    raise SystemExit(1 if failed else 0)
