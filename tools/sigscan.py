import sys
sigs = {
    b'PHCM': 'Microchip MEC EC image tag (MCHP)',
    b'MCHP': 'Microchip literal',
    b'$FPT': 'Intel ME Flash Partition Table',
    b'_FVH': 'UEFI Firmware Volume header',
    b'\x5a\xa5\xf0\x0f': 'Intel Flash Descriptor FLVALSIG',
    b'ITE ': 'ITE EC',
    b'IT85': 'ITE IT85xx',
    b'IT89': 'ITE IT89xx',
    b'ENE ': 'ENE EC',
    b'KB90': 'ENE KB90xx',
    b'NPCE': 'Nuvoton NPCE EC',
    b'WPCE': 'Nuvoton WPCE',
    b'SMSC': 'SMSC EC',
    b'Nuvoton': 'Nuvoton literal',
    b'eSPI': 'eSPI string',
    b'Dell Inc': 'Dell copyright',
}
path=sys.argv[1]
data=open(path,'rb').read()
print(f"### {path}  ({len(data)} bytes / {len(data)//1024//1024}MiB)")
for sig,desc in sigs.items():
    idxs=[]
    start=0
    while True:
        i=data.find(sig,start)
        if i<0: break
        idxs.append(i)
        start=i+1
        if len(idxs)>=12: break
    if idxs:
        shown=' '.join(f'0x{x:X}' for x in idxs[:12])
        more='' if len(idxs)<12 else ' ...'
        print(f"  {sig!r:>12} {desc:<40} x{len(idxs)}: {shown}{more}")
