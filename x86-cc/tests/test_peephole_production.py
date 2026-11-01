"""Verify production peephole actually fires, while O0 preserves baseline."""
import os
import subprocess
import tempfile
from pathlib import Path
ROOT=Path(__file__).resolve().parent.parent
CC=ROOT/('x86-cc.exe' if os.name=='nt' else 'x86-cc')
with tempfile.TemporaryDirectory(prefix='x86cc-prod-peephole-') as td:
    paths={}
    for level in ('O0','O1'):
        target=Path(td)/(level+'.asm')
        p=subprocess.run([str(CC),'-'+level,'-S',str(ROOT/'tests'/'if_true.c'),'-o',str(target)],capture_output=True,text=True)
        assert p.returncode==0,(level,p.stdout,p.stderr)
        paths[level]=target.read_text()
    pattern='    mov ax, bp\n    sub ax, 2\n    mov ax, [bp-2]\n'
    assert '    mov ax, [bp-2]\n' in paths['O1']
    assert '    mov ax, bp\n    sub ax, 2\n    mov ax, [bp-2]\n' not in paths['O1']
    assert '    mov ax, bp\n    mov bx, 2\n    sub ax, bx\n    mov ax, [bp-2]\n' in paths['O0']
    assert '    cmp ax, bx\n' in paths['O1']
print('PASS production peephole positive O1 and preserved O0 baseline')
