import pathlib,re,subprocess
root=pathlib.Path(__file__).parent
src=(root/'frame_slots_ping_regression.c').read_text()
items=list(re.finditer(r'message\("[^"]*"\);',src))
cc='O:/x86/toolchain/x86-cc/x86-cc.exe'
print('message calls',len(items))
for i,m in enumerate(items):
    text=src[:m.start()]+';'+src[m.end():]
    p=root/'frame_slots_one_removed.c';p.write_text(text)
    r=subprocess.run([cc,'-c','--blackjack',str(p),'-o',str(root/'frame_slots_one_removed.o')],capture_output=True,text=True)
    print(i,repr(m.group()),'PASS' if r.returncode==0 else 'FAIL',r.stderr.strip()[:120])
