"""Faithful Python port of bacher09/pwgen-for-bios Dell service-tag keygen.

Ported verbatim from src/keygen/dell/{encode,index}.ts so we can (a) validate our
understanding against the published test vectors and (b) reuse the exact
block-encode family + output pipeline when hunting for the undocumented CF1B
variant. Not for redistribution of the upstream project; this is a reference
oracle for the recovery task.

All arithmetic is 32-bit. JS `| 0` / `>>> 0` map to `& 0xFFFFFFFF`; JS signed `>>`
after `& 0xFF` masking is equivalent to unsigned here (see index.ts byte
extraction), so we keep everything unsigned.
"""
from __future__ import annotations

M = 0xFFFFFFFF


def to32(x: int) -> int:
    return x & M


def NOT(x: int) -> int:
    return (~x) & M


def rol(x: int, r: int) -> int:
    x &= M
    return ((x >> (32 - r)) | ((x << r) & M)) & M


# --- round functions (encode.ts) -------------------------------------------
def encF2(a, b, c):
    return (((c ^ b) & a) ^ c) & M


def encF3(a, b, c):
    return (((a ^ b) & c) ^ b) & M


def encF4(a, b, c):
    return ((b ^ a) ^ c) & M


def encF5(a, b, c):
    return ((a | NOT(c)) ^ b) & M


def encF1(a, b):
    return (a + b) & M


def encF1N(a, b):
    return (a - b) & M


def encF2N(a, b, c):
    return encF2(a, b, NOT(c))


def encF4N(a, b, c):
    return encF4(a, NOT(b), c)


def encF5N(a, b, c):
    return encF5(NOT(a), b, c)


md5magic = [
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
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x4881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
]

md5magic2 = [
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

rotationTable = [
    [7, 12, 17, 22],
    [5, 9, 14, 20],
    [4, 11, 16, 23],
    [6, 10, 15, 21],
]

initialData = [0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476]

scanCodes = ("\0\x1B1234567890-=\x08\x09qwertyuiop[]\x0D\xFF"
             "asdfghjkl;'`\xFF\\zxcvbnm,./")

encscans = [
    0x05, 0x10, 0x13, 0x09, 0x32, 0x03, 0x25, 0x11, 0x1F, 0x17, 0x06, 0x15,
    0x30, 0x19, 0x26, 0x22, 0x0A, 0x02, 0x2C, 0x2F, 0x16, 0x14, 0x07, 0x18,
    0x24, 0x23, 0x31, 0x20, 0x1E, 0x08, 0x2D, 0x21, 0x04, 0x0B, 0x12, 0x2E,
]

asciiPrintable = ("012345679abcdefghijklmnopqrstuvwxyz"
                  "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0")

extraCharacters = {
    "2A7B": asciiPrintable,
    "1F5A": asciiPrintable,
    "1D3B": "0BfIUG1kuPvc8A9Nl5DLZYSno7Ka6HMgqsJWm65yCQR94b21OTp7VFX2z0jihE33d4xtrew0",
    "1F66": "0ewr3d4xtUG1ku0BfIp7VFb21OTSno7KDLZYqsJWa6HMgCQR94m65y9Nl5Pvc8AjihE3X2z0",
    "6FF1": "08rptBxfbGVMz38IiSoeb360MKcLf4QtBCbWVzmH5wmZUcRR5DZG2xNCEv1nFtzsZB2bw1X0",
    "BF97": "0Q2drGk99rkQFMxN[Z5y3DGr16h638myIL2rzz2pzcU7JWLJ1EGnqRN4seZPRM2aBXIjbkGZ",
}


# --- encoder family (encode.ts) --------------------------------------------
class Tag595BEncoder:
    md5table = md5magic

    def __init__(self, encBlock):
        self.encBlock = list(encBlock)
        self.encData = self.initial_data()
        self.A, self.B, self.C, self.D = self.encData

    # round-function selection (595B uses the "negative" variants)
    def f1(self, a, b):
        return encF1N(a, b)

    def f2(self, a, b, c):
        return encF2N(a, b, c)

    def f3(self, a, b, c):
        return encF3(a, b, c)

    def f4(self, a, b, c):
        return encF4N(a, b, c)

    def f5(self, a, b, c):
        return encF5N(a, b, c)

    def initial_data(self):
        return list(initialData)

    def mtab(self, idx):
        return self.md5table[idx] if 0 <= idx < len(self.md5table) else 0

    def calculate(self, func, key1, key2):
        temp = func(self.B, self.C, self.D)
        return (self.A + self.f1(temp, (self.mtab(key2) + self.encBlock[key1]) & M)) & M

    def make_encode(self):
        for i in range(64):
            q = i >> 4
            if q == 0:
                t = self.calculate(self.f2, i & 15, i)
            elif q == 1:
                t = self.calculate(self.f3, (i * 5 + 1) & 15, i)
            elif q == 2:
                t = self.calculate(self.f4, (i * 3 + 5) & 15, i)
            else:
                t = self.calculate(self.f5, (i * 7) & 15, i)
            self.A = self.D
            self.D = self.C
            self.C = self.B
            self.B = (rol(t, rotationTable[q][i & 3]) + self.B) & M
        self.increment_data()

    def increment_data(self):
        self.encData[0] = (self.encData[0] + self.A) & M
        self.encData[1] = (self.encData[1] + self.B) & M
        self.encData[2] = (self.encData[2] + self.C) & M
        self.encData[3] = (self.encData[3] + self.D) & M

    def result(self):
        return [v & M for v in self.encData]

    @classmethod
    def encode(cls, encBlock):
        obj = cls(encBlock)
        obj.make_encode()
        return obj.result()


class TagD35BEncoder(Tag595BEncoder):
    def f1(self, a, b):
        return encF1(a, b)

    def f2(self, a, b, c):
        return encF2(a, b, c)

    def f3(self, a, b, c):
        return encF3(a, b, c)

    def f4(self, a, b, c):
        return encF4(a, b, c)

    def f5(self, a, b, c):
        return encF5(a, b, c)


class Tag1D3BEncoder(Tag595BEncoder):
    def make_encode(self):
        for j in range(21):
            self.A = (self.A | 0x97) & M
            self.B = (self.B ^ 0x8) & M
            self.C = (self.C | to32(0x60606161 - j)) & M
            self.D = (self.D ^ to32(0x50501010 + j)) & M
            super().make_encode()


class Tag1F66Encoder(Tag595BEncoder):
    md5table = md5magic2

    def make_encode(self):
        for j in range(17):
            self.A = (self.A | 0x100097) & M
            self.B = (self.B ^ 0xA0008) & M
            self.C = (self.C | to32(0x60606161 - j)) & M
            self.D = (self.D ^ to32(0x50501010 + j)) & M
            for i in range(64):
                q = i >> 4
                if q == 0:
                    t = self.calculate(self.f2, i & 15, i + 16)
                elif q == 1:
                    t = self.calculate(self.f3, (i * 5 + 1) & 15, i + 32)
                elif q == 2:
                    t = self.calculate(self.f4, (i * 3 + 5) & 15, i - 2 * (i & 12) + 12)
                else:
                    t = self.calculate(self.f5, (i * 7) & 15, 2 * (i & 3) - (i & 15) + 12)
                self.A = self.D
                self.D = self.C
                self.C = self.B
                self.B = (rol(t, rotationTable[q][i & 3]) + self.B) & M
            self.increment_data()

        for j in range(21):
            self.A = (self.A | 0x97) & M
            self.B = (self.B ^ 0x8) & M
            self.C = (self.C | to32(0x50501010 - j)) & M
            self.D = (self.D ^ to32(0x60606161 + j)) & M
            for i in range(64):
                q = i >> 4
                if q == 0:
                    t = self.calculate(self.f4, (i * 3 + 5) & 15, 2 * (i & 3) - i + 44)
                elif q == 1:
                    t = self.calculate(self.f5, (i * 7) & 15, 2 * (i & 3) - i + 76)
                elif q == 2:
                    t = self.calculate(self.f2, i & 15, (i & 15))
                else:
                    t = self.calculate(self.f3, (i * 5 + 1) & 15, i - 32)
                g = (i >> 4) + 2
                self.A = self.D
                self.D = self.C
                self.C = self.B
                self.B = (rol(t, rotationTable[g & 3][i & 3]) + self.B) & M
            self.increment_data()


class Tag6FF1Encoder(Tag595BEncoder):
    md5table = md5magic2
    counter1 = 23

    def make_encode(self):
        for j in range(self.counter1):
            self.A = (self.A | 0xA08097) & M
            self.B = (self.B ^ 0xA010908) & M
            self.C = (self.C | to32(0x60606161 - j)) & M
            self.D = (self.D ^ to32(0x50501010 + j)) & M
            for i in range(64):
                q = i >> 4
                k = (i & 15) - ((i & 12) << 1) + 12
                if q == 0:
                    t = self.calculate(self.f2, i & 15, i + 32)
                elif q == 1:
                    t = self.calculate(self.f3, (i * 5 + 1) & 15, (i & 15))
                elif q == 2:
                    t = self.calculate(self.f4, (i * 3 + 5) & 15, k + 16)
                else:
                    t = self.calculate(self.f5, (i * 7) & 15, k + 48)
                self.A = self.D
                self.D = self.C
                self.C = self.B
                self.B = (rol(t, rotationTable[q][i & 3]) + self.B) & M
            self.increment_data()

        for j in range(17):
            self.A = (self.A | 0x100097) & M
            self.B = (self.B ^ 0xA0008) & M
            self.C = (self.C | to32(0x50501010 - j)) & M
            self.D = (self.D ^ to32(0x60606161 + j)) & M
            for i in range(64):
                q = i >> 4
                k = (i & 15) - ((i & 12) << 1) + 12
                if q == 0:
                    t = self.calculate(self.f4, ((i & 15) * 3 + 5) & 15, k + 16)
                elif q == 1:
                    t = self.calculate(self.f5, ((i & 3) * 7 + (i & 12) + 4) & 15, (i & 15) + 32)
                elif q == 2:
                    t = self.calculate(self.f2, k & 15, k)
                else:
                    t = self.calculate(self.f3, ((i & 15) * 5 + 1) & 15, (i & 15) + 48)
                g = (i >> 4) + 2
                self.A = self.D
                self.D = self.C
                self.C = self.B
                self.B = (rol(t, rotationTable[g & 3][i & 3]) + self.B) & M
            self.increment_data()


class TagBF97Encoder(Tag6FF1Encoder):
    counter1 = 31


class Tag1F5AEncoder(Tag595BEncoder):
    md5table = md5magic2

    def calculate(self, func, key1, key2):
        temp = func(self.C, self.A, self.D)
        return (self.B + self.f1(temp, (self.mtab(key2) + self.encBlock[key1]) & M)) & M

    def make_encode(self):
        for _ in range(5):
            for j in range(64):
                q = j >> 4
                k = 12 + (j & 3) - (j & 12)
                if q == 0:
                    t = self.calculate(self.f2, j & 15, j)
                elif q == 1:
                    t = self.calculate(self.f3, (j * 5 + 1) & 15, j)
                elif q == 2:
                    t = self.calculate(self.f4, (j * 3 + 5) & 15, k + 0x20)
                else:
                    t = self.calculate(self.f5, (j * 7) & 15, k + 0x30)
                self.B = self.D
                self.D = self.A
                self.A = self.C
                self.C = (rol(t, rotationTable[q][j & 3]) + self.C) & M
            self.increment_data()

    def increment_data(self):
        self.encData[0] = (self.encData[0] + self.B) & M
        self.encData[1] = (self.encData[1] + self.C) & M
        self.encData[2] = (self.encData[2] + self.A) & M
        self.encData[3] = (self.encData[3] + self.D) & M


class TagE7A8Encoder(Tag595BEncoder):
    md5table = md5magic2
    loopParams = [17, 13, 12, 8]
    encodeParams = [
        0x50501010, 0xA010908, 0xA08097, 0x60606161,
        0x60606161, 0xA0008, 0x100097, 0x50501010,
    ]

    def initial_data(self):
        return [0, 0, 0, 0]

    def shortcut(self, fun, j, md5_index, rot_index, indexes):
        for i in range(4):
            t = self.calculate(fun, (j + indexes[i]) & 7, i + md5_index)
            self.A = self.D
            self.D = self.C
            self.C = self.B
            self.B = (rol(t, rotationTable[rot_index][i]) + self.B) & M

    def make_encode(self):
        for p in range(self.loopParams[0]):
            self.A = (self.A | self.encodeParams[0]) & M
            self.B = (self.B ^ self.encodeParams[1]) & M
            self.C = (self.C | to32(self.encodeParams[2] - p)) & M
            self.D = (self.D ^ to32(self.encodeParams[3] + p)) & M
            for j in range(0, self.loopParams[2], 4):
                self.shortcut(self.f2, j, j + 32, 0, [0, 1, 2, 3])
            for j in range(0, self.loopParams[2], 4):
                self.shortcut(self.f3, j, j, 1, [1, -2, -1, 0])
            j = self.loopParams[3]
            while j > 3:
                self.shortcut(self.f4, j, j + 16, 2, [-3, -4, -1, 2])
                j -= 4
            j = self.loopParams[3]
            while j > 3:
                self.shortcut(self.f5, j, j + 48, 3, [2, 3, 2, -3])
                j -= 4
            self.increment_data()

        for p in range(self.loopParams[1]):
            self.A = (self.A | self.encodeParams[4]) & M
            self.B = (self.B ^ self.encodeParams[5]) & M
            self.C = (self.C | to32(self.encodeParams[6] - p)) & M
            self.D = (self.D ^ to32(self.encodeParams[7] + p)) & M
            j = self.loopParams[3]
            while j > 3:
                self.shortcut(self.f4, j, j + 16, 2, [-3, -4, -1, 2])
                j -= 4
            for j in range(0, self.loopParams[2], 4):
                self.shortcut(self.f5, j, j + 32, 3, [2, 3, 2, -3])
            j = self.loopParams[3]
            while j > 0:
                self.shortcut(self.f2, j, j, 0, [0, 1, 2, 3])
                j -= 4
            for j in range(0, self.loopParams[2], 4):
                self.shortcut(self.f3, j, j + 48, 1, [1, -2, 3, 0])
            self.increment_data()


class TagE7A8EncoderSecond(TagE7A8Encoder):
    loopParams = [17, 13, 12, 16]
    md5table = md5magic2 + [
        0xa0008 ^ 0x6d2f93a5, 0xa08097 ^ 0x6d2f93a5,
        0xa010908 ^ 0x6d2f93a5, 0x60606161 ^ 0x6d2f93a5,
    ]


ENCODERS = {
    "595B": Tag595BEncoder,
    "2A7B": Tag595BEncoder,
    "A95B": Tag595BEncoder,
    "1D3B": Tag1D3BEncoder,
    "D35B": TagD35BEncoder,
    "1F66": Tag1F66Encoder,
    "6FF1": Tag6FF1Encoder,
    "1F5A": Tag1F5AEncoder,
    "BF97": TagBF97Encoder,
    "E7A8": TagE7A8Encoder,
}


# --- pipeline (index.ts) ----------------------------------------------------
def calculate_suffix(serial, tag, hdd=False):
    if not hdd:
        arr1 = [1, 2, 3, 4]
        arr2 = [4, 3, 2]
    else:
        arr1 = [1, 10, 9, 8]
        arr2 = [8, 9, 10]

    suf = [0] * 8
    suf[0] = serial[arr1[3]]
    suf[1] = (serial[arr1[3]] >> 5) | (((serial[arr1[2]] >> 5) | (serial[arr1[2]] << 3)) & 0xF1)
    suf[2] = serial[arr1[2]] >> 2
    suf[3] = (serial[arr1[2]] >> 7) | (serial[arr1[1]] << 1)
    suf[4] = (serial[arr1[1]] >> 4) | (serial[arr1[0]] << 4)
    suf[5] = serial[1] >> 1
    suf[6] = (serial[1] >> 6) | (serial[0] << 2)
    suf[7] = serial[0] >> 3
    suf = [v & 0xFF for v in suf]

    table = extraCharacters.get(tag)
    codes = [ord(c) for c in table] if table is not None else encscans

    out = []
    for i in range(8):
        r = 0xAA
        if suf[i] & 1:
            r ^= serial[arr2[0]]
        if suf[i] & 2:
            r ^= serial[arr2[1]]
        if suf[i] & 4:
            r ^= serial[arr2[2]]
        if suf[i] & 8:
            r ^= serial[1]
        if suf[i] & 16:
            r ^= serial[0]
        out.append(codes[r % len(codes)])
    return out


def _byte_array_to_int(arr):
    # 16 little-endian 32-bit words; missing bytes -> 0
    words = []
    for i in range(16):
        b0 = arr[i * 4] if i * 4 < len(arr) else 0
        b1 = arr[i * 4 + 1] if i * 4 + 1 < len(arr) else 0
        b2 = arr[i * 4 + 2] if i * 4 + 2 < len(arr) else 0
        b3 = arr[i * 4 + 3] if i * 4 + 3 < len(arr) else 0
        words.append((b0 | (b1 << 8) | (b2 << 16) | (b3 << 24)) & M)
    return words


def _int_array_to_byte(words):
    out = []
    for num in words:
        out.append(num & 0xFF)
        out.append((num >> 8) & 0xFF)
        out.append((num >> 16) & 0xFF)
        out.append((num >> 24) & 0xFF)
    return out


def result_to_string(arr, tag):
    r = arr[0] % 9
    res = ""
    table = extraCharacters.get(tag)
    for i in range(16):
        if table is not None:
            res += table[arr[i] % len(table)]
        elif r <= i and len(res) < 8:
            res += scanCodes[encscans[arr[i] % len(encscans)]]
    return res


def keygen_dell(serial, tag, hdd=False):
    """Service-tag path only fully supported here (hdd kept for completeness)."""
    if tag == "A95B":
        full = serial + "595B" if not hdd else serial[3:] + "\0\0\0" + "595B"
    else:
        full = serial + tag

    arr = [ord(c) & 0xFF for c in full]

    if tag == "E7A8":
        block = _byte_array_to_int(arr)
        results = []
        from hashlib import sha256
        table = "Q92G0drk9y63r5DG1hLqJGW1EnRk[QxrFMNZ328I6myLr4MsPNeZR2z72czpzUJBGXbaIjkZ"
        for klass in (TagE7A8Encoder, TagE7A8EncoderSecond):
            res_bytes = _int_array_to_byte(klass.encode(block))
            out = sha256(bytes(res_bytes)).digest()
            s = "".join(table[(out[i + 16] + out[i]) % len(table)] for i in range(16))
            results.append(s)
        return results

    arr = arr + calculate_suffix(arr, tag, hdd)
    cnt = 23
    while len(arr) <= cnt:
        arr.append(0)
    arr[cnt] = 0x80
    block = _byte_array_to_int(arr)
    block[14] = cnt << 3
    decoded = _int_array_to_byte(ENCODERS[tag].encode(block))
    out = result_to_string(decoded, tag)
    return [out] if out else []


def keygen_service_tag(system_number):
    tag = system_number[7:11].upper()
    serial = system_number[:7].upper()
    return keygen_dell(serial, tag, hdd=False)
