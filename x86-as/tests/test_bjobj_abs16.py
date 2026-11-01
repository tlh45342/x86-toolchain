import os, subprocess, sys
from pathlib import Path

HERE=Path(__file__).resolve().parent
ROOT=HERE.parent
BUILD=HERE/'build'
BUILD.mkdir(exist_ok=True)

def exe(name, local_root):
    p=local_root/(name+'.exe' if os.name=='nt' else name)
    return str(p) if p.exists() else name

src=HERE/'039_bjobj_abs16_local.asm'
obj=BUILD/'039_bjobj_abs16_local.o'
out=BUILD/'039_bjobj_abs16_local.bin'
assembler=exe('x86-as',ROOT)
linker=exe('x86-ld',ROOT.parent/'x86-ld')

for cmd in (
    [assembler,'-f','bjobj',str(src),'-o',str(obj)],
    [linker,'-m','blackjack16','-Ttext','0x8000',str(obj),'-o',str(out)],
):
    r=subprocess.run(cmd,capture_output=True,text=True)
    if r.returncode:
        print('FAIL', ' '.join(cmd))
        print(r.stdout); print(r.stderr)
        raise SystemExit(1)

data=out.read_bytes()
# Local data begins after 10 instructions + HLT.  Derive the expected linked
# addresses from the final byte layout so the test checks relocation, not a
# hand-maintained magic offset.
byte_off=len(data)-5
word_off=byte_off+1
byte_addr=0x8000+byte_off
word_addr=0x8000+word_off
w=lambda x: bytes((x&255,(x>>8)&255))
expected=(b'\xA1'+w(word_addr)+b'\xA3'+w(word_addr)+
          b'\xA0'+w(byte_addr)+b'\xA2'+w(byte_addr)+
          b'\x8B\x1E'+w(word_addr)+b'\x89\x1E'+w(word_addr)+
          b'\x8E\x06'+w(word_addr)+b'\x8C\x06'+w(word_addr)+
          b'\xA1'+w(word_addr+2)+b'\xA3'+w(word_addr+2)+b'\xF4')
if data[:len(expected)] != expected:
    print('FAIL BJOBJ ABS16 local relocation')
    print(' expected',expected.hex())
    print(' got     ',data[:len(expected)].hex())
    raise SystemExit(1)
print('039_bjobj_abs16_local   PASS')
