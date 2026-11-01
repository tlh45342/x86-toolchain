"""Verify actual BJO3 TEXT/DATA/BSS records and DATA16 relocation."""
from pathlib import Path
import struct
import subprocess

root = Path(__file__).resolve().parents[1]
source = root / 'tests' / 'bjo3_multisection.asm'
output = root / 'tests' / 'bjo3_multisection.o'
subprocess.run([str(root / 'x86-as.exe'), '-f', 'bjobj3', str(source), '-o', str(output)], check=True)
data = output.read_bytes()
assert data[:4] == b'BJO3'
assert struct.unpack_from('<H', data, 4)[0] == 3
position = 8
sections = []
for _ in range(3):
    name = data[position:position + 64].split(b'\0')[0].decode()
    kind, flags, align, size, payload_size = struct.unpack_from('<IIIII', data, position + 64)
    position += 84
    payload = data[position:position + payload_size]
    position += payload_size
    sections.append((name, kind, size, payload))
assert [section[0] for section in sections] == ['.text', '.data', '.bss'], sections
assert sections[0][3][0] == 0xa1, sections
assert sections[1] == ('.data', 1, 2, bytes.fromhex('2a00')), sections
assert sections[2] == ('.bss', 2, 32, b''), sections
symbol_count = struct.unpack_from('<H', data, position)[0]
position += 2
symbols = {}
for _ in range(symbol_count):
    name = data[position:position + 64].split(b'\0')[0].decode()
    section, binding, offset = struct.unpack_from('<HHI', data, position + 64)
    symbols[name] = (section, offset)
    position += 72
assert symbols == {'entry': (1, 0), 'counter': (2, 0), 'scratch': (3, 0)}, symbols
reloc_count = struct.unpack_from('<H', data, position)[0]
position += 2
assert reloc_count == 1, reloc_count
assert struct.unpack_from('<HH', data, position) == (1, 4)
print('PASS BJO3 TEXT/DATA/BSS and DATA16 relocation')
