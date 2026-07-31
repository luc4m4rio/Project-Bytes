#!/usr/bin/env python3
"""
Dell 8FC8 master-password keygen.

Port of the community Dell keygen framework (Tag595BEncoder / TagE7A8Encoder /
TagE7A8EncoderSecond, plus the `calculateE7A8` SHA-256 + seed-map post-process),
adapted for suffix 8FC8 with the alphabet extracted from the DellSecurityVaultSmm
module at VA 0xA280.
"""

from __future__ import annotations
import hashlib
import struct

MASK = 0xFFFFFFFF

# ────────────────────────────────────────────────────────────────
# MD5 magic tables
# ────────────────────────────────────────────────────────────────
MD5_MAGIC = [
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
]

MD5_MAGIC_2 = [
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
]

ROTATION_TABLE = [
    [7, 12, 17, 22],
    [5,  9, 14, 20],
    [4, 11, 16, 23],
    [6, 10, 15, 21],
]

INITIAL_DATA_MD5 = [0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476]


# ────────────────────────────────────────────────────────────────
# f-functions
# ────────────────────────────────────────────────────────────────
def _not(x: int) -> int:
    return (~x) & MASK

# positive variants (standard MD5)
def f2(b, c, d): return (((d ^ c) & b) ^ d) & MASK
def f3(b, c, d): return (((b ^ c) & d) ^ c) & MASK
def f4(b, c, d): return ((c ^ b) ^ d) & MASK
def f5(b, c, d): return ((b | _not(d)) ^ c) & MASK

# negative variants (Tag595B / TagE7A8 family)
def f2N(b, c, d): return f2(b, c, _not(d))
def f4N(b, c, d): return f4(b, _not(c), d)
def f5N(b, c, d): return f5(_not(b), c, d)

def f1(x, y):  return (x + y) & MASK
def f1N(x, y): return (x - y) & MASK

def rol(x: int, n: int) -> int:
    x &= MASK
    n &= 31
    return ((x << n) | (x >> (32 - n))) & MASK


# ────────────────────────────────────────────────────────────────
# Tag595BEncoder — the "basic" MD5-variant, negative f-functions
# ────────────────────────────────────────────────────────────────
class Tag595B:
    md5table = MD5_MAGIC
    f1 = staticmethod(f1N)
    f2 = staticmethod(f2N)
    f3 = staticmethod(f3)
    f4 = staticmethod(f4N)
    f5 = staticmethod(f5N)

    def __init__(self, block):
        self.encBlock = [b & MASK for b in block]
        self.encData = self.initial_data()
        self.A, self.B, self.C, self.D = self.encData

    def initial_data(self):
        return list(INITIAL_DATA_MD5)

    def calculate(self, fn, k1, k2):
        temp = fn(self.B, self.C, self.D)
        inner = (self.md5table[k2] + self.encBlock[k1]) & MASK
        return (self.A + self.f1(temp, inner)) & MASK

    def make_encode(self):
        for i in range(64):
            r = i >> 4
            if r == 0:   t = self.calculate(self.f2, i & 15, i)
            elif r == 1: t = self.calculate(self.f3, (i * 5 + 1) & 15, i)
            elif r == 2: t = self.calculate(self.f4, (i * 3 + 5) & 15, i)
            else:        t = self.calculate(self.f5, (i * 7) & 15, i)
            self.A = self.D
            self.D = self.C
            self.C = self.B
            self.B = (rol(t, ROTATION_TABLE[r][i & 3]) + self.B) & MASK
        self._increment_data()

    def _increment_data(self):
        self.encData[0] = (self.encData[0] + self.A) & MASK
        self.encData[1] = (self.encData[1] + self.B) & MASK
        self.encData[2] = (self.encData[2] + self.C) & MASK
        self.encData[3] = (self.encData[3] + self.D) & MASK

    def result(self):
        return [v & MASK for v in self.encData]

    @classmethod
    def encode(cls, block):
        obj = cls(block)
        obj.make_encode()
        return obj.result()


# ────────────────────────────────────────────────────────────────
# TagE7A8Encoder
# ────────────────────────────────────────────────────────────────
class TagE7A8(Tag595B):
    md5table = MD5_MAGIC_2
    loopParams = [17, 13, 12, 8]
    encodeParams = [
        0x50501010, 0x0A010908, 0x00A08097, 0x60606161,
        0x60606161, 0x000A0008, 0x00100097, 0x50501010,
    ]

    def initial_data(self):
        return [0, 0, 0, 0]

    def _shortcut(self, fn, j, md5_index, rot_index, indexes):
        for i in range(4):
            t = self.calculate(fn, (j + indexes[i]) & 7, i + md5_index)
            self.A = self.D
            self.D = self.C
            self.C = self.B
            self.B = (rol(t, ROTATION_TABLE[rot_index][i]) + self.B) & MASK

    def make_encode(self):
        lp = self.loopParams
        ep = self.encodeParams

        # first outer loop
        for p in range(lp[0]):
            self.A = (self.A | ep[0]) & MASK
            self.B = (self.B ^ ep[1]) & MASK
            self.C = (self.C | ((ep[2] - p) & MASK)) & MASK
            self.D = (self.D ^ ((ep[3] + p) & MASK)) & MASK

            for j in range(0, lp[2], 4):
                self._shortcut(self.f2, j, j + 32, 0, [0, 1, 2, 3])
            for j in range(0, lp[2], 4):
                self._shortcut(self.f3, j, j,      1, [1, -2, -1, 0])
            j = lp[3]
            while j > 3:
                self._shortcut(self.f4, j, j + 16, 2, [-3, -4, -1, 2])
                j -= 4
            j = lp[3]
            while j > 3:
                self._shortcut(self.f5, j, j + 48, 3, [2, 3, 2, -3])
                j -= 4
            self._increment_data()

        # second outer loop
        for p in range(lp[1]):
            self.A = (self.A | ep[4]) & MASK
            self.B = (self.B ^ ep[5]) & MASK
            self.C = (self.C | ((ep[6] - p) & MASK)) & MASK
            self.D = (self.D ^ ((ep[7] + p) & MASK)) & MASK

            j = lp[3]
            while j > 3:
                self._shortcut(self.f4, j, j + 16, 2, [-3, -4, -1, 2])
                j -= 4
            for j in range(0, lp[2], 4):
                self._shortcut(self.f5, j, j + 32, 3, [2, 3, 2, -3])
            j = lp[3]
            while j > 0:
                self._shortcut(self.f2, j, j,      0, [0, 1, 2, 3])
                j -= 4
            for j in range(0, lp[2], 4):
                self._shortcut(self.f3, j, j + 48, 1, [1, -2, 3, 0])
            self._increment_data()


# ────────────────────────────────────────────────────────────────
# TagE7A8EncoderSecond — buggy overflow variant
# ────────────────────────────────────────────────────────────────
_OVERFILL = [
    0x000A0008 ^ 0x6d2f93a5,
    0x00A08097 ^ 0x6d2f93a5,
    0x0A010908 ^ 0x6d2f93a5,
    0x60606161 ^ 0x6d2f93a5,
]

class TagE7A8Second(TagE7A8):
    md5table = MD5_MAGIC_2 + _OVERFILL
    loopParams = [17, 13, 12, 16]


# ────────────────────────────────────────────────────────────────
# Tag1D3B — Tag595B wrapped in 21 outer rounds with A/B/C/D mods
# ────────────────────────────────────────────────────────────────
class Tag1D3B(Tag595B):
    def make_encode(self):
        for j in range(21):
            self.A = (self.A | 0x97) & MASK
            self.B = (self.B ^ 0x8) & MASK
            self.C = (self.C | ((0x60606161 - j) & MASK)) & MASK
            self.D = (self.D ^ ((0x50501010 + j) & MASK)) & MASK
            super().make_encode()


# ────────────────────────────────────────────────────────────────
# Tag1F66
# ────────────────────────────────────────────────────────────────
class Tag1F66(Tag595B):
    md5table = MD5_MAGIC_2

    def make_encode(self):
        for j in range(17):
            self.A = (self.A | 0x100097) & MASK
            self.B = (self.B ^ 0xA0008) & MASK
            self.C = (self.C | ((0x60606161 - j) & MASK)) & MASK
            self.D = (self.D ^ ((0x50501010 + j) & MASK)) & MASK
            for i in range(64):
                r = i >> 4
                if r == 0:   t = self.calculate(self.f2, i & 15, i + 16)
                elif r == 1: t = self.calculate(self.f3, (i*5+1) & 15, i + 32)
                elif r == 2: t = self.calculate(self.f4, (i*3+5) & 15, i - 2*(i & 12) + 12)
                else:        t = self.calculate(self.f5, (i*7) & 15, 2*(i & 3) - (i & 15) + 12)
                self.A = self.D; self.D = self.C; self.C = self.B
                self.B = (rol(t, ROTATION_TABLE[r][i & 3]) + self.B) & MASK
            self._increment_data()
        for j in range(21):
            self.A = (self.A | 0x97) & MASK
            self.B = (self.B ^ 0x8) & MASK
            self.C = (self.C | ((0x50501010 - j) & MASK)) & MASK
            self.D = (self.D ^ ((0x60606161 + j) & MASK)) & MASK
            for i in range(64):
                r = i >> 4
                if r == 0:   t = self.calculate(self.f4, (i*3+5) & 15, 2*(i & 3) - i + 44)
                elif r == 1: t = self.calculate(self.f5, (i*7) & 15, 2*(i & 3) - i + 76)
                elif r == 2: t = self.calculate(self.f2, i & 15, i & 15)
                else:        t = self.calculate(self.f3, (i*5+1) & 15, i - 32)
                g = (r + 2) & 3
                self.A = self.D; self.D = self.C; self.C = self.B
                self.B = (rol(t, ROTATION_TABLE[g][i & 3]) + self.B) & MASK
            self._increment_data()


# ────────────────────────────────────────────────────────────────
# Tag6FF1
# ────────────────────────────────────────────────────────────────
class Tag6FF1(Tag595B):
    md5table = MD5_MAGIC_2
    counter1 = 23

    def make_encode(self):
        for j in range(self.counter1):
            self.A = (self.A | 0xA08097) & MASK
            self.B = (self.B ^ 0xA010908) & MASK
            self.C = (self.C | ((0x60606161 - j) & MASK)) & MASK
            self.D = (self.D ^ ((0x50501010 + j) & MASK)) & MASK
            for i in range(64):
                r = i >> 4
                k = (i & 15) - ((i & 12) << 1) + 12
                if r == 0:   t = self.calculate(self.f2, i & 15, i + 32)
                elif r == 1: t = self.calculate(self.f3, (i*5+1) & 15, i & 15)
                elif r == 2: t = self.calculate(self.f4, (i*3+5) & 15, k + 16)
                else:        t = self.calculate(self.f5, (i*7) & 15, k + 48)
                self.A = self.D; self.D = self.C; self.C = self.B
                self.B = (rol(t, ROTATION_TABLE[r][i & 3]) + self.B) & MASK
            self._increment_data()
        for j in range(17):
            self.A = (self.A | 0x100097) & MASK
            self.B = (self.B ^ 0xA0008) & MASK
            self.C = (self.C | ((0x50501010 - j) & MASK)) & MASK
            self.D = (self.D ^ ((0x60606161 + j) & MASK)) & MASK
            for i in range(64):
                r = i >> 4
                k = (i & 15) - ((i & 12) << 1) + 12
                if r == 0:   t = self.calculate(self.f4, ((i & 15) * 3 + 5) & 15, k + 16)
                elif r == 1: t = self.calculate(self.f5, ((i & 3) * 7 + (i & 12) + 4) & 15, (i & 15) + 32)
                elif r == 2: t = self.calculate(self.f2, k & 15, k)
                else:        t = self.calculate(self.f3, ((i & 15) * 5 + 1) & 15, (i & 15) + 48)
                g = (r + 2) & 3
                self.A = self.D; self.D = self.C; self.C = self.B
                self.B = (rol(t, ROTATION_TABLE[g][i & 3]) + self.B) & MASK
            self._increment_data()


class TagBF97(Tag6FF1):
    counter1 = 31


# ────────────────────────────────────────────────────────────────
# Tag1F5A — swapped A/B/C/D rotation, custom incrementData
# ────────────────────────────────────────────────────────────────
class Tag1F5A(Tag595B):
    md5table = MD5_MAGIC_2

    def calculate(self, fn, k1, k2):
        temp = fn(self.C, self.A, self.D)
        inner = (self.md5table[k2] + self.encBlock[k1]) & MASK
        return (self.B + self.f1(temp, inner)) & MASK

    def _increment_data(self):
        self.encData[0] = (self.encData[0] + self.B) & MASK
        self.encData[1] = (self.encData[1] + self.C) & MASK
        self.encData[2] = (self.encData[2] + self.A) & MASK
        self.encData[3] = (self.encData[3] + self.D) & MASK

    def make_encode(self):
        for _ in range(5):
            for j in range(64):
                r = j >> 4
                k = 12 + (j & 3) - (j & 12)
                if r == 0:   t = self.calculate(self.f2, j & 15, j)
                elif r == 1: t = self.calculate(self.f3, (j*5+1) & 15, j)
                elif r == 2: t = self.calculate(self.f4, (j*3+5) & 15, k + 0x20)
                else:        t = self.calculate(self.f5, (j*7) & 15, k + 0x30)
                self.B = self.D; self.D = self.A; self.A = self.C
                self.C = (rol(t, ROTATION_TABLE[r][j & 3]) + self.C) & MASK
            self._increment_data()


# ────────────────────────────────────────────────────────────────
# 8FC8 alphabet (SEED at VA 0xA280 in DellSecurityVaultSmm)
# ────────────────────────────────────────────────────────────────
SEED_8FC8 = "0Q2drGk99WLJ1EGnqR5y3DGr16hN4seZPRM2zz2pzcU7JaBXIjbkGZrkQFMxN[Z638myIL2r"
assert len(SEED_8FC8) == 72


# ────────────────────────────────────────────────────────────────
# encBlock packing — mirrors the TS `byteArrayToInt` on `serial + tag`
# ────────────────────────────────────────────────────────────────
def build_encBlock(serial: str, suffix: str, u32_len: int = 16) -> list[int]:
    """Concatenate serial+suffix as ASCII bytes, pack LE into u32_len uint32s."""
    b = (serial + suffix).encode("ascii")
    padded = b + b"\x00" * (u32_len * 4 - len(b))
    return list(struct.unpack("<%dI" % u32_len, padded[: u32_len * 4]))


def _u32_to_bytes_le(arr):
    return b"".join(struct.pack("<I", v & MASK) for v in arr)


# ────────────────────────────────────────────────────────────────
# calculateE7A8 flow, generalised — inner encoder + SHA-256 + seed map
# ────────────────────────────────────────────────────────────────
def format_password(encoder_result_u32, seed: str) -> str:
    inner16 = _u32_to_bytes_le(encoder_result_u32)      # 16 bytes
    digest  = hashlib.sha256(inner16).digest()          # 32 bytes
    return "".join(seed[(digest[i] + digest[i + 16]) % len(seed)] for i in range(16))


def keygen_8FC8(serial: str) -> list[str]:
    """Return both master-password candidates for a 7-char service tag under suffix 8FC8."""
    assert len(serial) == 7
    block = build_encBlock(serial.upper(), "8FC8", u32_len=16)
    return [
        format_password(TagE7A8      .encode(block), SEED_8FC8),
        format_password(TagE7A8Second.encode(block), SEED_8FC8),
    ]


if __name__ == "__main__":
    import sys
    for tag in sys.argv[1:]:
        pws = keygen_8FC8(tag)
        for pw in pws:
            print(f"{tag.upper()}-8FC8  {pw}")
