import os,subprocess
from pathlib import Path
HERE=Path(__file__).resolve().parent; ROOT=HERE.parent; BUILD=HERE/'build'; BUILD.mkdir(exist_ok=True)
def exe(name,root):
 p=root/(name+'.exe' if os.name=='nt' else name); return str(p) if p.exists() else name
src=HERE/'040_bjobj_abs16_matrix.asm'; obj=BUILD/'040_bjobj_abs16_matrix.o'; out=BUILD/'040_bjobj_abs16_matrix.bin'
for cmd in ([exe('x86-as',ROOT),'-f','bjobj',str(src),'-o',str(obj)],[exe('x86-ld',ROOT.parent/'x86-ld'),'-m','blackjack16','-Ttext','0x8000',str(obj),'-o',str(out)]):
 r=subprocess.run(cmd,capture_output=True,text=True)
 if r.returncode: print(r.stderr); raise SystemExit(1)
data=out.read_bytes(); target=0x8000+len(data)-4; lo=target&255; hi=target>>8
# Every direct [target] displacement must be the linked address.  A surviving
# object-relative target has high byte 00 and is precisely the bug class.
hits=0
for i in range(len(data)-1):
 if data[i]==lo:
  if data[i+1]==hi: hits+=1
  elif data[i+1]==0:
   print(f'FAIL unrelocated ABS16 candidate at file offset 0x{i:04X}: {lo:02X}00 expected {target:04X}')
   raise SystemExit(1)
if hits < 16:
 print(f'FAIL expected at least 16 relocated target references, found {hits}')
 print(data.hex()); raise SystemExit(1)
print(f'040_bjobj_abs16_matrix  PASS ({hits} relocated references)')
