"""Positive and negative tests of the actual C peephole scanner."""
import subprocess
import tempfile
from pathlib import Path
HERE=Path(__file__).resolve().parent
cases=[
 ("dead_flags","mov ax, bp\nsub ax, 2\nmov ax, [bp-2]\npush ax\nmov bx, 4\ncmp ax, bx\n",True),
 ("flags_read","mov ax, bp\nsub ax, 2\nmov ax, [bp-2]\njz done\n",False),
 ("label_barrier","mov ax, bp\nsub ax, 2\nmov ax, [bp-2]\ndone:\ncmp ax, 0\n",False),
 ("unknown_barrier","mov ax, bp\nsub ax, 2\nmov ax, [bp-2]\nrep movsw\ncmp ax, 0\n",False),
 ("call_barrier","mov ax, bp\nsub ax, 2\nmov ax, [bp-2]\ncall f\ncmp ax, 0\n",False),
 ("flag_kill","mov ax, bp\nsub ax, 2\nmov ax, [bp-2]\ncmp ax, 0\n",True),
 ("inc_preserves_cf","mov ax, bp\nsub ax, 2\nmov ax, [bp-2]\ninc bx\njc taken\n",False),
 ("clc_partial_flags","mov ax, bp\nsub ax, 2\nmov ax, [bp-2]\nclc\njz taken\n",False),
 ("self_move","mov bx, bx\nmov ax, ax\ncmp ax, 0\n",True),
 ("segment_self_move","mov ds, ds\ncmp ax, 0\n",False),
]
with tempfile.TemporaryDirectory(prefix="peephole-analyzer-") as td:
    work=Path(td)
    exe=work/"driver.exe"
    p=subprocess.run(["gcc","-std=c11","-Wall","-Wextra",str(HERE/"peephole_driver.c"),"-o",str(exe)],capture_output=True,text=True)
    assert p.returncode==0,(p.stdout,p.stderr)
    for name,source,should_change in cases:
        f=work/(name+".asm")
        for level in (1,0):
            f.write_text(source)
            p=subprocess.run([str(exe),str(f),str(level)],capture_output=True,text=True)
            assert p.returncode==0,(name,p.stderr)
            assert (f.read_text()!=source)==(should_change and level==1),name
        print("PASS",name)
print("PASS C analyzer safety cases:",len(cases))
