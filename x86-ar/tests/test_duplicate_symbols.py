import pathlib, subprocess, tempfile, shutil
ROOT=pathlib.Path(__file__).resolve().parents[1]
LD=ROOT.parent/'x86-ld'/'x86-ld.exe'
AR=ROOT/'x86-ar.exe'
NM=ROOT.parent/'x86-nm'/'x86-nm.exe'

def obj(path,defs=(),refs=()):
    syms=[(name,0,1) for name in defs]+[(name,0,0) for name in refs]
    raw=b'BJO1'+(1).to_bytes(4,'little')+len(syms).to_bytes(2,'little')+len(refs).to_bytes(2,'little')
    for name,val,defined in syms:
        raw+=name.encode().ljust(64,b'\0')+val.to_bytes(4,'little')+bytes([defined])
    for name in refs:
        raw+=name.encode().ljust(64,b'\0')+(0).to_bytes(4,'little')+bytes([1])
    path.write_bytes(raw+b'\x00\x00\xc3' if refs else raw+b'\xc3')

def run(*args,ok=True):
    p=subprocess.run(list(map(str,args)),capture_output=True,text=True)
    if (p.returncode==0)!=ok: raise AssertionError(f'{args}: rc={p.returncode}\n{p.stdout}\n{p.stderr}')
    return p

with tempfile.TemporaryDirectory() as td:
    p=pathlib.Path(td)
    obj(p/'main.o',('_start',))
    obj(p/'duplicate.o',('_start',))
    obj(p/'helper.o',('helper',))
    # A direct duplicate must always be rejected.
    r=run(LD,'-m','blackjack16',p/'main.o',p/'duplicate.o','-o',p/'bad.bin',ok=False)
    assert 'duplicate symbol' in r.stderr, r.stderr
    print('PASS: direct duplicate definition rejected')
    # The archive must retain both objects and the linker must ignore an unused duplicate.
    run(AR,'rcs',p/'libtest.a',p/'duplicate.o',p/'helper.o')
    r=run(AR,'t',p/'libtest.a')
    assert r.stdout.splitlines()==['duplicate.o','helper.o'],r.stdout
    print('PASS: archive retains duplicate definition without error')
    symbols=run(NM,p/'libtest.a').stdout
    assert 'T _start' in symbols and 'T helper' in symbols,symbols
    print('PASS: x86-nm inspects archived BJO1 symbols')
    extracted=p/'extract'; extracted.mkdir()
    subprocess.run([str(AR),'x',str(p/'libtest.a')],cwd=extracted,check=True)
    assert (extracted/'duplicate.o').read_bytes()==(p/'duplicate.o').read_bytes()
    assert (extracted/'helper.o').read_bytes()==(p/'helper.o').read_bytes()
    print('PASS: archive extraction byte-for-byte roundtrip')
    run(LD,'-m','blackjack16',p/'main.o',p/'libtest.a','-o',p/'ok.bin')
    print('PASS: unreferenced archive duplicate ignored')
    # When a selected archive member conflicts with an existing definition, reject it.
    obj(p/'main2.o',('_start','helper'))
    obj(p/'needs.o',('entry',),('helper',))
    run(AR,'rcs',p/'libconflict.a',p/'needs.o',p/'helper.o')
    # Selected member itself defines _start, conflicting with main.o.
    obj(p/'conflict.o',('_start','wanted'))
    run(AR,'rcs',p/'libselected.a',p/'conflict.o')
    obj(p/'caller.o',('_start',),('wanted',))
    r=run(LD,'-m','blackjack16',p/'caller.o',p/'libselected.a','-o',p/'conflict.bin',ok=False)
    assert 'duplicate symbol' in r.stderr,r.stderr
    print('PASS: selected archive duplicate rejected')




