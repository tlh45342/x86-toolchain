from pathlib import Path
root=Path(__file__).resolve().parent.parent
p=root/'Makefile'
s=p.read_text()
assert '$(TARGET): x86-cc.c\n' in s
p.write_text(s.replace('$(TARGET): x86-cc.c\n','$(TARGET): x86-cc.c peephole.h\n'))
p=root/'tests'/'test_peephole_analyzer.py'
s=p.read_text()
needle=' ("self_move","mov bx, bx\\nmov ax, ax\\ncmp ax, 0\\n",True),'
assert needle in s
s=s.replace(needle,' ("inc_preserves_cf","mov ax, bp\\nsub ax, 2\\nmov ax, [bp-2]\\ninc bx\\njc taken\\n",False),\n ("clc_partial_flags","mov ax, bp\\nsub ax, 2\\nmov ax, [bp-2]\\nclc\\njz taken\\n",False),\n'+needle)
p.write_text(s)
print('Header dependency and partial-flags negative cases added')
