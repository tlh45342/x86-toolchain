import subprocess
import tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parent.parent

def asm(code, level):
    with tempfile.TemporaryDirectory() as tmp:
        src = Path(tmp) / 'a.c'
        dst = Path(tmp) / 'a.asm'
        src.write_text(code)
        p = subprocess.run([str(ROOT / 'x86-cc.exe'), level, '-S', str(src), '-o', str(dst)], capture_output=True, text=True)
        assert p.returncode == 0, p.stderr
        return dst.read_text()

source = 'int main(){int x; x=1; if(x) x=2; else x=3; return x;}'
old = asm(source, '-O0')
new = asm(source, '-O1')
assert '.Lif_body_' in old
assert '.Lif_body_' in new
assert 'jmp .Lif_body_' in new
assert 'jmp .Lif_else_' in new
assert '.Lcc_long_skip_' in new
source = 'struct pair {int a; int b;}; int main(){struct pair p; p.b=7; return p.b;}'
old = asm(source, '-O0')
new = asm(source, '-O1')
assert 'mov bx, 2' in old
assert 'add ax, 2' in new
print('PASS sprint5 displacement and sprint6 branch')
