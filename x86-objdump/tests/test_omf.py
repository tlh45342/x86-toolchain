"""OMF reader interoperability and malformed-object regression tests."""
import pathlib
import shutil
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
ASM = ROOT / 'tests' / 'omf_smoke.asm'
OBJ = ROOT / 'tests' / 'omf_smoke.obj'
DUMP = ROOT / ('x86-objdump.exe' if sys.platform == 'win32' else 'x86-objdump')
NASM = shutil.which('nasm')
if not NASM:
    print('SKIP OMF NASM reference (nasm unavailable)')
    sys.exit(0)
subprocess.run([NASM, '-f', 'obj', str(ASM), '-o', str(OBJ)], check=True)
result = subprocess.run([str(DUMP), str(OBJ)], capture_output=True, text=True)
assert result.returncode == 0, result.stderr
for record in ('THEADR', 'SEGDEF', 'PUBDEF', 'LEDATA', 'MODEND', 'records verified'):
    assert record in result.stdout, (record, result.stdout)
invalid = OBJ.with_suffix('.bad.obj')
try:
    content = bytearray(OBJ.read_bytes())
    content[-1] ^= 0x01
    invalid.write_bytes(content)
    result = subprocess.run([str(DUMP), str(invalid)], capture_output=True, text=True)
    assert result.returncode != 0 and 'checksum' in result.stderr.lower(), result.stderr
finally:
    invalid.unlink(missing_ok=True)
print('PASS OMF NASM interoperability and checksum rejection')
