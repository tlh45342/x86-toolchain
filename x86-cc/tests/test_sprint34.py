"""Focused optimizer assembly checks. Uses local compiler, not installed one."""
import subprocess
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
CC = ROOT / 'x86-cc.exe'


def assembly(code, level):
    with tempfile.TemporaryDirectory() as td:
        src, dst = Path(td) / 'case.c', Path(td) / 'case.asm'
        src.write_text(code)
        p = subprocess.run([str(CC), level, '-S', str(src), '-o', str(dst)],
                           capture_output=True, text=True)
        assert p.returncode == 0, p.stderr
        return dst.read_text()


def test():
    a = assembly('int main(){int x; x=3; return x*8;}', '-O0')
    b = assembly('int main(){int x; x=3; return x*8;}', '-O1')
    assert 'mul bx' in a
    assert b.count('shl ax, 1') >= 3 and 'mul bx' not in b
    for op in ('&&', '||'):
        code = f'int main(){{int a; a=1; return a {op} 2;}}'
        s = assembly(code, '-O1')
        assert '.Land_rhs_' not in s and '.Lor_rhs_' not in s
    print('PASS sprint3 strength reduction and sprint4 short-circuit branches')

if __name__ == '__main__':
    test()
