"""Package a linked libxenon ELF for XeLL (USB-root xenon.elf).

Extracted from Codex's xbox360/startup_probe.py. XeLL expects the LOAD segments'
physical addresses below 0x80000000, so the freshly linked ELF is converted with
--adjust-vma 0x80000000, stripped, and its program headers are checked.

Always package the freshly linked original, never an intermediate object or an
already-packaged file.

Usage:
    python3 xbox/tools/package_xell.py --prefix "$DEVKITXENON" linked.elf out/xenon.elf
"""
import argparse
import hashlib
import json
import struct
import subprocess
from pathlib import Path


def tool(prefix, name):
    return str(Path(prefix) / 'bin' / ('xenon-' + name))


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument('--prefix', type=Path, required=True, help='devkitxenon install ($DEVKITXENON)')
    p.add_argument('original', type=Path)
    p.add_argument('packaged', type=Path)
    a = p.parse_args()

    a.packaged.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run([tool(a.prefix, 'objcopy'), '-O', 'elf32-powerpc', '--adjust-vma', '0x80000000',
                    str(a.original), str(a.packaged)], check=True)
    subprocess.run([tool(a.prefix, 'strip'), str(a.packaged)], check=True)

    data = a.packaged.read_bytes()
    if data[:6] != b'\x7fELF\x01\x02' or struct.unpack_from('>H', data, 18)[0] != 20:
        raise SystemExit('Expected ELF32 big-endian PowerPC')
    offset = struct.unpack_from('>I', data, 28)[0]
    size, count = struct.unpack_from('>HH', data, 42)
    loads = []
    for i in range(count):
        kind, file_offset, virtual, physical, file_size, memory_size, _, _ = struct.unpack_from('>8I', data, offset + i * size)
        if kind != 1:
            continue
        if file_size > memory_size or file_offset + file_size > len(data):
            raise SystemExit('Invalid LOAD file range')
        if physical + memory_size >= 0x80000000:
            raise SystemExit('XeLL LOAD addresses remain unadjusted')
        loads.append(dict(physical=hex(physical), virtual=hex(virtual), memory_size=memory_size))
    if not loads:
        raise SystemExit('Missing LOAD segment')

    info = dict(path=str(a.packaged), bytes=len(data), sha256=hashlib.sha256(data).hexdigest(), loads=loads)
    a.packaged.with_suffix('.json').write_text(json.dumps(info, indent=2))
    print('XeLL package:', a.packaged)


if __name__ == '__main__':
    main()
