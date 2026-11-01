"""Run both optimization levels in x86-run, compare expected AX and HLT.
Guest-step limits are safety bounds, NOT performance measurements.
"""
import os
import shutil
import subprocess
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
HERE = ROOT / 'tests'
CC = ROOT / ('x86-cc.exe' if os.name == 'nt' else 'x86-cc')
VM = os.environ.get('X86_RUN', 'x86-run')
CASES = (('return42',42),('struct_basic',42),('struct_typed_layout',42),
         ('if_true',42),('if_else_blocks',42),('long_if_body',42),
         ('logical_and_true',42),('logical_or_false',42),
         ('runtime_mul_locals',42),('array_loop',42),('large_local_array',42))

def run(command, **kw):
    p = subprocess.run(command, capture_output=True, text=True, cwd=ROOT, **kw)
    assert p.returncode == 0, f'{command}: {p.stdout} {p.stderr}'
    return p

def main():
    assert shutil.which(VM), f'VM unavailable: {VM}'
    template = (HERE / 'test.script.in').read_text()
    with tempfile.TemporaryDirectory(prefix='x86cc-execution-') as td:
        folder = Path(td)
        for stem, expected in CASES:
            for level in ('O0', 'O1'):
                binary = folder / f'{stem}-{level}.bin'
                log = folder / f'{stem}-{level}.log'
                run([str(CC), '-' + level, str(HERE / (stem + '.c')), '-o', str(binary)])
                script = template.replace('@BIN@', str(binary)).replace('@LOG@', str(log))
                run([VM], input=script)
                assert log.exists(), f'{stem} {level}: missing VM log'
                contents = log.read_text()
                assert f'AX={expected & 65535:04X}' in contents, f'{stem} {level}: AX mismatch'
                assert 'hlt' in contents.lower(), f'{stem} {level}: HLT missing'
            print('PASS', stem, 'O0/O1 AX and HLT')
    print('PASS execution equivalence:', len(CASES), 'programs, both levels')

if __name__ == '__main__':
    main()
