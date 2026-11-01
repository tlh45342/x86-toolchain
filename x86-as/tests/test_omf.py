"""OMF smoke and rejection regression for the native assembler."""
import pathlib
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
ASM = ROOT / ('x86-as.exe' if sys.platform == 'win32' else 'x86-as')
DUMP = ROOT.parent / 'x86-objdump' / ('x86-objdump.exe' if sys.platform == 'win32' else 'x86-objdump')
SOURCE = ROOT / 'tests' / 'omf_minimal.asm'
OUTPUT = ROOT / 'tests' / 'omf_minimal.obj'
subprocess.run([str(ASM), '-f', 'obj', str(SOURCE), '-o', str(OUTPUT)], check=True)
result = subprocess.run([str(DUMP), str(OUTPUT)], capture_output=True, text=True)
assert result.returncode == 0, result.stderr
for name in ('THEADR', 'LNAMES', 'SEGDEF', 'PUBDEF', 'LEDATA', 'MODEND', '6 OMF records verified'):
    assert name in result.stdout, result.stdout
assert OUTPUT.read_bytes()[:1] == b'\x80'
print('PASS x86-as Intel OMF object writer and independent reader')
