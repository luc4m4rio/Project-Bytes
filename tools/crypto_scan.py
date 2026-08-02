#!/usr/bin/env python3
"""Scan a firmware blob for cryptographic / encoding fingerprints.

Detects (byte-exact where possible):
  - SHA-256 round-constant table K[0..63]
  - SHA-1 / MD5 init + SHA-1 round constants
  - MD5 T[] constants
  - CRC-32 (reflected) lookup table + polynomial 0xEDB88320
  - CRC-32/BE polynomial 0x04C11DB7, CRC-32C
  - AES forward / inverse S-box
  - base-N (itoa) digit table, and crypto-relevant strings

Usage: python3 crypto_scan.py <blob.bin> [vma_base]
       vma_base (optional, default 0xBFCF0000 minus 0x40) maps region offset->VMA
       for the 3310 MEC payload; pass 0 to report raw offsets only.
"""
import sys, struct

def sha256_K():
    import math
    primes=[]; n=2
    while len(primes)<64:
        if all(n%p for p in primes): primes.append(n)
        n+=1
    return [int((p**(1/3.0) % 1)*(1<<32)) & 0xFFFFFFFF for p in primes]

def crc32_table(poly=0xEDB88320):
    t=[]
    for i in range(256):
        c=i
        for _ in range(8): c=(poly^(c>>1)) if c&1 else c>>1
        t.append(c & 0xFFFFFFFF)
    return t

AES_SBOX = bytes.fromhex(
 "637c777bf26b6fc53001672bfed7ab76ca82c97dfa5947f0add4a2af9ca472c0"
 "b7fd9326363ff7cc34a5e5f171d8311504c723c31896059a071280e2eb27b275")

def le32(b,o): return struct.unpack_from("<I",b,o)[0]

def find_table(data, tbl, minmatch):
    """Find longest region where consecutive dwords match tbl; return (offset,matched)."""
    pref=b''.join(struct.pack("<I",x) for x in tbl[:8])
    o=data.find(pref)
    if o<0: return None
    m=sum(1 for i in range(len(tbl)) if o+4*i+4<=len(data) and le32(data,o+4*i)==tbl[i])
    return (o,m) if m>=minmatch else None

def main():
    path=sys.argv[1]
    base=int(sys.argv[2],0) if len(sys.argv)>2 else (0xBFCF0000-0x40)
    data=open(path,"rb").read()
    vma=(lambda o:base+o) if base else (lambda o:None)
    def rep(name,o,extra=""):
        v=vma(o); loc=f"region 0x{o:X}"+(f" VMA 0x{v:08X}" if v is not None else "")
        print(f"  [+] {name:34s} {loc}  {extra}")

    print(f"# crypto/encoding scan of {path} ({len(data)} bytes)")
    # SHA-256
    r=find_table(data, sha256_K(), 8)
    if r: rep("SHA-256 K-table", r[0], f"{r[1]}/64 entries")
    # CRC-32 reflected
    r=find_table(data, crc32_table(0xEDB88320), 16)
    if r: rep("CRC-32 reflected table", r[0], f"{r[1]}/256 entries")
    for poly,label in [(0xEDB88320,"CRC-32 poly (reflected)"),(0x04C11DB7,"CRC-32 poly (BE)"),
                       (0x82F63B78,"CRC-32C poly")]:
        o=data.find(struct.pack("<I",poly))
        if o>=0: rep(label, o, f"0x{poly:08X}")
    # SHA-1 / MD5 constants
    for c,label in [(0x67452301,"SHA-1/MD5 init H0"),(0xC3D2E1F0,"SHA-1 init H4"),
                    (0x5A827999,"SHA-1 round K0"),(0xD76AA478,"MD5 T[1]")]:
        o=data.find(struct.pack("<I",c))
        if o>=0: rep(label,o,f"0x{c:08X}")
    # AES
    o=data.find(AES_SBOX[:32])
    if o>=0: rep("AES forward S-box",o)
    o=data.find(bytes.fromhex("52096ad53036a538bf40a39e81f3d7fb"))
    if o>=0: rep("AES inverse S-box",o)
    # encoding table + strings
    for s,label in [(b"abcdefghijklmnopqrstuvwxyz","base-N digit table (itoa/%x)"),
                    (b"VerifyEcSdsaSignature","SDSA signature-verify routine"),
                    (b"dellbatterydell","Dell battery-auth tag"),
                    (b"Espi_send_slave_boot_load","eSPI slave-boot loader")]:
        o=data.find(s)
        if o>=0: rep(label,o)

if __name__=="__main__":
    main()
