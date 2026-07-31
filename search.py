#!/usr/bin/env python3
"""Broad grid search over (inner encoder × encBlock construction × state layout ×
seed indexer) for the 8FC8 recipe. Success = all 12 known pairs reproduce."""

from __future__ import annotations
import hashlib
import struct
import itertools

from keygen import (
    Tag595B, TagE7A8, TagE7A8Second, Tag1D3B, Tag1F66, Tag6FF1, TagBF97, Tag1F5A,
    MD5_MAGIC, MD5_MAGIC_2, MASK, SEED_8FC8,
    f1, f2, f3, f4, f5,
)

PAIRS = [
    ("BC91NL3", "2XykI691322s03r4"),
    ("H9ZLSL3", "JR0WnRPERzRQzNq["),
    ("8VRTSL3", "msffe422daw5jde4"),
    ("9I87UL3", "mdgrr42PKq4hdr58"),
    ("FVTLLS3", "4Zh8hMBcksLEBM19"),
    ("8709FK3", "qnprBM2PP3rzLck2"),
    ("1NXQU23", "1BGLGGUJUjxZj12G"),
    ("5SR8TL3", "aUr[hhIRskszkpsM"),
    ("31WYGS3", "JQMLk265rz3QIkQI"),
    ("4GMSTL3", "sLkNM[BQ4L4Ixm34"),
    ("RE4FSE3", "Lsp01Mq8zZ42GzI["),
    ("GHJTR23", "xzdkGyjz6E9k3522"),
]


class TagD35B(Tag595B):
    f1 = staticmethod(f1); f2 = staticmethod(f2); f3 = staticmethod(f3); f4 = staticmethod(f4); f5 = staticmethod(f5)

class Tag595B_MD2(Tag595B):
    md5table = MD5_MAGIC_2

class Tag595B_zero(Tag595B):
    def initial_data(self): return [0, 0, 0, 0]

class TagD35B_MD2(TagD35B):
    md5table = MD5_MAGIC_2

class TagD35B_zero(TagD35B):
    def initial_data(self): return [0, 0, 0, 0]


ENCODERS = {
    "Tag595B"       : Tag595B,
    "Tag595B_MD2"   : Tag595B_MD2,
    "Tag595B_zero"  : Tag595B_zero,
    "TagD35B"       : TagD35B,
    "TagD35B_MD2"   : TagD35B_MD2,
    "TagD35B_zero"  : TagD35B_zero,
    "TagE7A8"       : TagE7A8,
    "TagE7A8Second" : TagE7A8Second,
    "Tag1D3B"       : Tag1D3B,
    "Tag1F66"       : Tag1F66,
    "Tag6FF1"       : Tag6FF1,
    "TagBF97"       : TagBF97,
    "Tag1F5A"       : Tag1F5A,
}


def _u32_le(a): return b"".join(struct.pack("<I", v & MASK) for v in a)


def pack_le(s: bytes, u32_len=16):
    padded = s + b"\x00" * (u32_len * 4 - len(s))
    return list(struct.unpack("<%dI" % u32_len, padded[: u32_len * 4]))


# encBlock builders → return list of 16 uint32 (padded)
def eb_(serial: str, extra_bytes: bytes, u32_len=16):
    return pack_le(serial.encode() + extra_bytes, u32_len)

BUILDERS = {
    "serial+8FC8"        : lambda s: eb_(s, b"8FC8"),
    "serial only"        : lambda s: eb_(s, b""),
    "8FC8+serial"        : lambda s: pack_le(b"8FC8" + s.encode()),
    "serial+E7A8"        : lambda s: eb_(s, b"E7A8"),
    "serial+8FC8+80"     : lambda s: eb_(s, b"8FC8\x80"),
    "serial+80"          : lambda s: eb_(s, b"\x80"),
    "u16 serial+8FC8"    : lambda s: pack_le(b"".join(struct.pack("<H", ord(c)) for c in (s + "8FC8"))),
    "u16 serial"         : lambda s: pack_le(b"".join(struct.pack("<H", ord(c)) for c in s)),
    "serial+u16(0x8FC8)" : lambda s: eb_(s, struct.pack("<H", 0x8FC8)),
    "serial+u32(0x8FC8)" : lambda s: eb_(s, struct.pack("<I", 0x8FC8)),
    "serial+u16(0xC88F)" : lambda s: eb_(s, struct.pack("<H", 0xC88F)),
    "serial+hex(8FC8)"   : lambda s: eb_(s, bytes.fromhex("8FC8")),
    "8FC8 as u32+serial" : lambda s: pack_le(struct.pack("<I", 0x8FC8) + s.encode()),
    "serial+#8FC8"       : lambda s: eb_(s, b"#8FC8"),
    "serial+8fc8(lc)"    : lambda s: eb_(s, b"8fc8"),
    "serial+8FC8 md5pad" : lambda s: _md5pad(s.encode() + b"8FC8"),
}

def _md5pad(b: bytes) -> list[int]:
    l = len(b) * 8
    b = b + b"\x80"
    while len(b) % 64 != 56:
        b += b"\x00"
    b = b + struct.pack("<Q", l)
    return pack_le(b, u32_len=len(b) // 4)


# state builders: (inner16: bytes, encBlock: list[int]) -> 32 bytes
def sha256(inner, eb):     return hashlib.sha256(inner).digest()
def sha256_eb(inner, eb):  return hashlib.sha256(_u32_le(eb)).digest()
def sha256_inner_eb(inner, eb): return hashlib.sha256(inner + _u32_le(eb)).digest()
def sha256_eb_inner(inner, eb): return hashlib.sha256(_u32_le(eb) + inner).digest()
def sha256_inner_reversed(inner, eb): return hashlib.sha256(inner[::-1]).digest()

def double_sha256(inner, eb): return hashlib.sha256(hashlib.sha256(inner).digest()).digest()
def sha256_by_pair_swap(inner, eb):
    d = hashlib.sha256(inner).digest()
    return d[16:] + d[:16]

def inner_double(inner, eb):
    return inner + inner
def inner_zero(inner, eb):
    return inner + b"\x00" * 16
def zero_inner(inner, eb):
    return b"\x00" * 16 + inner

def inner_eb_first16(inner, eb):
    return inner + _u32_le(eb)[:16]
def inner_eb_last16(inner, eb):
    return inner + _u32_le(eb)[16:32]
def eb_first16_inner(inner, eb):
    return _u32_le(eb)[:16] + inner
def eb_last16_inner(inner, eb):
    return _u32_le(eb)[16:32] + inner

def inner_be_double(inner, eb):
    return inner[::-1] + inner
def double_swap(inner, eb):
    a = inner
    return a[8:] + a[:8] + a[:8] + a[8:]

def eb_direct(inner, eb):
    return _u32_le(eb)[:32]

def md5_pair(inner, eb):
    return hashlib.md5(inner).digest() + hashlib.md5(_u32_le(eb)).digest()

STATES = {
    "sha256(inner)"          : sha256,
    "sha256(eb)"             : sha256_eb,
    "sha256(inner||eb)"      : sha256_inner_eb,
    "sha256(eb||inner)"      : sha256_eb_inner,
    "sha256(inner)[swap16]"  : sha256_by_pair_swap,
    "sha256(reversed inner)" : sha256_inner_reversed,
    "double sha256"          : double_sha256,
    "inner||inner"           : inner_double,
    "inner||0"               : inner_zero,
    "0||inner"               : zero_inner,
    "inner||eb[0..15]"       : inner_eb_first16,
    "inner||eb[16..31]"      : inner_eb_last16,
    "eb[0..15]||inner"       : eb_first16_inner,
    "eb[16..31]||inner"      : eb_last16_inner,
    "eb[0..31]"              : eb_direct,
    "md5(inner)||md5(eb)"    : md5_pair,
}


def format_pw_add(state):
    return "".join(SEED_8FC8[(state[i] + state[i + 16]) % 72] for i in range(16))

def format_pw_xor(state):
    return "".join(SEED_8FC8[(state[i] ^ state[i + 16]) % 72] for i in range(16))

def format_pw_sub(state):
    return "".join(SEED_8FC8[(state[i] - state[i + 16]) % 72] for i in range(16))

def format_pw_add_rev(state):
    return "".join(SEED_8FC8[(state[16-1-i] + state[32-1-i]) % 72] for i in range(16))

MAPPERS = {
    "add":     format_pw_add,
    "xor":     format_pw_xor,
    "sub":     format_pw_sub,
    "add_rev": format_pw_add_rev,
}


def check(enc_cls, eb_fn, state_fn, mapper_fn):
    for tag, exp in PAIRS:
        block = eb_fn(tag)
        if len(block) < 16: block += [0] * (16 - len(block))
        try:
            h = enc_cls.encode(block[:16])
        except Exception:
            return False
        inner = _u32_le(h)
        state = state_fn(inner, block)
        if len(state) < 32:
            return False
        got = mapper_fn(state[:32])
        if got != exp:
            return False
    return True


def main():
    total = len(ENCODERS) * len(BUILDERS) * len(STATES) * len(MAPPERS)
    print(f"Trying {total} combos...")
    hits = []
    checked = 0
    for (en_name, en_cls), (eb_name, eb_fn), (st_name, st_fn), (mp_name, mp_fn) in itertools.product(
        ENCODERS.items(), BUILDERS.items(), STATES.items(), MAPPERS.items()
    ):
        checked += 1
        # First-pair fast fail
        tag0, exp0 = PAIRS[0]
        block = eb_fn(tag0)
        if len(block) < 16: block += [0] * (16 - len(block))
        try:
            h = en_cls.encode(block[:16])
        except Exception:
            continue
        inner = _u32_le(h)
        state = st_fn(inner, block)
        if len(state) < 32: continue
        got = mp_fn(state[:32])
        if got != exp0:
            continue
        # verify all pairs
        if check(en_cls, eb_fn, st_fn, mp_fn):
            hits.append((en_name, eb_name, st_name, mp_name))
            print("HIT:", hits[-1])
    print(f"\nChecked {checked} combos, {len(hits)} hit(s).")

if __name__ == "__main__":
    main()
