from pathlib import Path
import os, shutil, subprocess, sys
HERE=Path(__file__).resolve().parent
ROOT=HERE.parent
AS=os.environ.get('X86_AS','x86-as')
CC=os.environ.get('X86_CC','x86-cc')
LD=str(ROOT/('x86-ld.exe' if os.name=='nt' else 'x86-ld'))
VM=os.environ.get('X86_RUN','x86-run')
B=HERE/'build'/'blackjack16'
shutil.rmtree(B,ignore_errors=True); B.mkdir(parents=True)
def run(a,inp=None): return subprocess.run(a,input=inp,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
def need(p,label):
 if p.returncode: print(p.stdout); print('FAIL',label); sys.exit(1)
entry=B/'entry.asm'; answer=HERE/'bj_answer.c'
entry.write_text('cpu 8086\nbits 16\nglobal _start\nextern answer\n_start:\n    call answer\n    hlt\n')
need(run([AS,'-f','bjobj',str(entry),'-o',str(B/'entry.o')]),'assemble entry')
need(run([CC,'-c',str(answer),'-o',str(B/'answer.o')]),'compile C object')
need(run([LD,'-m','blackjack16',str(B/'entry.o'),str(B/'answer.o'),'-o',str(B/'mixed.bin')]),'link mixed objects')
data=(B/'mixed.bin').read_bytes()
if data[:4] != bytes.fromhex('e8 01 00 f4'): print('FAIL PC16 relocation',data.hex(' ')); sys.exit(1)
print('PASS blackjack16 ASM -> C PC16 relocation')
# ABS16: object-local symbolic address must acquire both object placement and link base.
absasm=B/'abs16.asm'
absasm.write_text('cpu 8086\nbits 16\nglobal _start\n_start:\n    mov ax, msg\n    hlt\nmsg:\n    dw 0x1234\n')
need(run([AS,'-f','bjobj',str(absasm),'-o',str(B/'abs16.o')]),'assemble ABS16')
need(run([LD,'-m','blackjack16','-Ttext','0x8000',str(B/'abs16.o'),'-o',str(B/'abs16.bin')]),'link ABS16')
adata=(B/'abs16.bin').read_bytes()
if adata != bytes.fromhex('b8 04 80 f4 34 12'): print('FAIL ABS16 relocation',adata.hex(' ')); sys.exit(1)
print('PASS blackjack16 ABS16 relocation at 0x8000')
farasm=B/'far_entry.asm'
farasm.write_text('cpu 8086\nbits 16\nglobal _start\nextern answer\n_start:\n    call far answer\n    hlt\n')
need(run([AS,'-f','bjobj',str(farasm),'-o',str(B/'far_entry.o')]),'assemble FAR32')
need(run([LD,'-m','blackjack16','-Ttext','0x8000',str(B/'far_entry.o'),str(B/'answer.o'),'-o',str(B/'far.bin')]),'link FAR32')
fardata=(B/'far.bin').read_bytes()
if fardata[:5] != bytes.fromhex('9a 06 00 00 08'): print('FAIL FAR32',fardata[:5].hex(' '));sys.exit(1)
print('PASS blackjack16 FAR32 cross-object relocation')
# Medium ABI smoke test: far CALL must pair with a far RET, including
# restoration of the caller's CS and IP. This is distinct from the
# relocation-byte test above, which used a Small-model C callee.
medium_c=B/'medium_answer.c'
medium_c.write_text('int answer(void) { return 42; }\n')
need(run([CC,'--model=medium','-c',str(medium_c),'-o',str(B/'medium_answer.o')]),'compile medium C callee')
need(run([LD,'-m','blackjack16','-Ttext','0x8000',str(B/'far_entry.o'),str(B/'medium_answer.o'),'-o',str(B/'medium_far.bin')]),'link medium far smoke')
medium_cases = [
 ('args', 'int add(int a,int b){return a+b;} int answer(void){return add(19,23);}\n'),
 ('nested', 'int leaf(int x){return x+1;} int middle(int x){return leaf(x+1);} int answer(void){return middle(40);}\n'),
 ('global', 'int value=41; int answer(void){return value+1;}\n'),
 ('locals', 'int worker(int a,int b){int local[4]; local[0]=a; local[1]=b; local[2]=local[0]+local[1]; local[3]=local[2]+1; return local[3];} int answer(void){return worker(18,23);}\n'),
 ('pointer', 'int add(int *p){return *p+1;} int answer(void){int value=41; return add(&value);}\n'),
 ('recursion', 'int recur(int n){if(n==0)return 42; return recur(n-1);} int answer(void){return recur(5);}\n'),
]
for name, source in medium_cases:
 src=B/f'medium_{name}.c'; src.write_text(source)
 need(run([CC,'--model=medium','-c',str(src),'-o',str(B/f'medium_{name}.o')]),f'compile medium {name}')
 need(run([LD,'-m','blackjack16','-Ttext','0x8000',str(B/'far_entry.o'),str(B/f'medium_{name}.o'),'-o',str(B/f'medium_{name}.bin')]),f'link medium {name}')
# Sweep 4: distinct CS placements for each BJO1 object in Medium mode.
need(run([LD,'-m','blackjack16-medium','-Ttext','0x8000',str(B/'far_entry.o'),str(B/'medium_answer.o'),'-o',str(B/'medium_segmented.bin')]),'link segmented medium')
segdata=(B/'medium_segmented.bin').read_bytes()
if segdata[:5] != bytes.fromhex('9a 00 00 01 08'):
 print('FAIL segmented far pointer',segdata[:5].hex(' '));sys.exit(1)
print('PASS medium distinct CS:IP relocation')
# BJO2 first-stage TEXT section and section-aware symbol/relocation records.
need(run([AS,'-f','bjobj2',str(B/'far_entry.asm'),'-o',str(B/'far_entry_bjo2.o')]),'assemble BJO2')
need(run([LD,'-m','blackjack16-medium','-Ttext','0x8000',str(B/'far_entry_bjo2.o'),str(B/'medium_answer.o'),'-o',str(B/'medium_bjo2.bin')]),'link mixed BJO2/BJO1')
if (B/'medium_bjo2.bin').read_bytes() != segdata:
 print('FAIL BJO2 relocation equivalence');sys.exit(1)
print('PASS BJO2 TEXT object and section-aware records')
# A large filler object forces the far-call target beyond physical 64K.
import struct
pad=B/'medium_padding.o'
pad.write_bytes(b'BJO1'+struct.pack('<IHH',36864,0,0)+bytes(36864))
need(run([LD,'-m','blackjack16-medium','-Ttext','0x8000',str(B/'far_entry.o'),str(pad),str(B/'medium_answer.o'),'-o',str(B/'medium_cross64.bin')]),'link cross-64K medium')
cross=(B/'medium_cross64.bin').read_bytes()
far_ip,far_cs=struct.unpack_from('<HH',cross,1)
if (far_cs<<4)+far_ip < 65536:
 print('FAIL medium target not beyond 64K');sys.exit(1)
print('PASS medium far relocation beyond physical 64K')
if shutil.which(VM):
 log=B/'mixed.log'; script=f'logfile {log}\nvm create\nset cpu debug=exec\nload {B/"mixed.bin"} 0000:1000\ncpu regs clear\nset IP 0x1000\nset run steps 5000\nrun\nregs\n'
 p=run([VM],script); text=log.read_text(errors='replace') if log.exists() else p.stdout
 if 'AX=002A' not in text or 'hlt' not in text.lower(): print(text); print('FAIL blackjack16 VM execution'); sys.exit(1)
 print('PASS blackjack16 mixed C/ASM VM execution AX=42')
 farlog=B/'medium_far.log'
 farscript=f'logfile {farlog}\nvm create\nset cpu debug=exec\nload {B/"medium_far.bin"} 0000:8000\ncpu regs clear\nset IP 0x8000\nset run steps 5000\nrun\nregs\n'
 p=run([VM],farscript)
 fartext=farlog.read_text(errors='replace') if farlog.exists() else p.stdout
 if 'AX=002A' not in fartext or 'hlt' not in fartext.lower():
  print(fartext); print('FAIL medium far CALL/RETF VM execution'); sys.exit(1)
 print('PASS medium far CALL/RETF VM execution AX=42')
 seglog=B/'medium_segmented.log'
 segscript=f'logfile {seglog}\nvm create\nset cpu debug=exec\nload {B/"medium_segmented.bin"} 0000:8000\ncpu regs clear\nset IP 0x8000\nset run steps 5000\nrun\nregs\n'
 segresult=run([VM],segscript)
 segtext=seglog.read_text(errors='replace') if seglog.exists() else segresult.stdout
 if not all(x in segtext for x in ('AX=002A','SP=FFFE','CS=0000 IP=8006','0801:0000')):
  print(segtext); print('FAIL segmented medium VM execution');sys.exit(1)
 print('PASS medium segmented far CALL/RETF VM execution AX=42')
 crosslog=B/'medium_cross64.log'
 crossscript=segscript.replace('medium_segmented','medium_cross64')
 crossresult=run([VM],crossscript)
 crosstext=crosslog.read_text(errors='replace') if crosslog.exists() else crossresult.stdout
 if not all(x in crosstext for x in ('AX=002A','SP=FFFE','CS=0000 IP=8006')):
  print(crosstext);print('FAIL medium cross-64K VM execution');sys.exit(1)
 print('PASS medium cross-64K VM execution AX=42')
 for name, _ in medium_cases:
  case_log=B/f'medium_{name}.log'
  case_script=f'logfile {case_log}\nvm create\nset cpu debug=exec\nload {B/f"medium_{name}.bin"} 0000:8000\ncpu regs clear\nset IP 0x8000\nset run steps 5000\nrun\nregs\n'
  result=run([VM],case_script)
  output=case_log.read_text(errors='replace') if case_log.exists() else result.stdout
  # Verify the far-return chain restored the caller's code segment,
  # instruction pointer, frame pointer and initial stack pointer.
  expected = ('AX=002A', 'BP=0000', 'SP=FFFE', 'CS=0000 IP=8006', 'SS=0000')
  if not all(field in output for field in expected) or 'hlt' not in output.lower():
   print(output); print(f'FAIL medium {name} VM execution'); sys.exit(1)
  print(f'PASS medium {name} VM execution AX=42')
else: print('SKIP VM execution (x86-run not found)')
print('PASS')
