"""Repeatable -O0/-O1 qualification: compile, assemble, and measure real bytes.

Execution equivalence remains the responsibility of run_tests.py; do not
confuse successful assembly or size changes with runtime speedups.
"""
import csv
import subprocess
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TESTS = ROOT / 'tests'
CC = ROOT / 'x86-cc.exe'
if not CC.exists():
    CC = ROOT / 'x86-cc'
SAMPLES = ('return42', 'large_local_array', 'struct_basic', 'struct_typed_layout',
           'if_true', 'if_else_blocks', 'long_if_body', 'logical_and_true',
           'logical_or_false', 'runtime_mul_locals', 'array_loop')

def compile_one(src, opt, output, asm):
    for args in ((opt, '-S', str(src), '-o', str(asm)),
                 (opt, str(src), '-o', str(output))):
        result = subprocess.run([str(CC), *args], cwd=ROOT, capture_output=True, text=True)
        assert result.returncode == 0, f'{src.name} {opt}: {result.stdout} {result.stderr}'
    assert output.is_file() and output.stat().st_size > 0, (src, opt)
    return output.stat().st_size, len(asm.read_text().splitlines())

def main():
    rows = []
    with tempfile.TemporaryDirectory(prefix='x86cc-opt-gate-') as td:
        folder = Path(td)
        for stem in SAMPLES:
            src = TESTS / (stem + '.c')
            assert src.is_file(), src
            sizes = {}
            for level in ('O0', 'O1'):
                binary = folder / (stem + '-' + level + '.bin')
                assembly = folder / (stem + '-' + level + '.asm')
                sizes[level] = compile_one(src, '-' + level, binary, assembly)
            rows.append((stem, sizes['O0'][0], sizes['O1'][0],
                         sizes['O1'][0] - sizes['O0'][0],
                         sizes['O0'][1], sizes['O1'][1]))
    print('sample,O0_binary_bytes,O1_binary_bytes,delta_bytes,O0_asm_lines,O1_asm_lines')
    for row in rows:
        print(','.join(map(str, row)))
    print('PASS optimization gate: compiled and assembled', len(rows), 'samples at both levels')

if __name__ == '__main__':
    main()
