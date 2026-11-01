from pathlib import Path
import subprocess, sys
H=Path(__file__).resolve().parent
R=H.parent
B=H/'build'/'kernel_end'
B.mkdir(parents=True,exist_ok=True)
def run(a):
 p=subprocess.run(a,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
 if p.returncode:
  print(p.stdout); sys.exit(1)
run(['x86-as','-f','bjobj',str(H/'bj_kernel_end.asm'),'-o',str(B/'kernel_end.o')])
run([str(R/'x86-ld.exe'),'-m','blackjack16','-Ttext','0x8000',str(B/'kernel_end.o'),'-o',str(B/'kernel_end.bin')])
b=(B/'kernel_end.bin').read_bytes()
if b != bytes.fromhex('e8 00 00'):
 print('FAIL kernel-end relocation',b.hex(' ')); sys.exit(1)
print('PASS blackjack16 linker-defined kernel-end symbol')
