from pathlib import Path
import os,subprocess,shutil,sys
here=Path(__file__).resolve().parent
root=here.parent
tool=root/("x86-objdump.exe" if os.name=="nt" else "x86-objdump")
b=here/"build";shutil.rmtree(b,ignore_errors=True);b.mkdir()
asm=b/"t.asm";asm.write_text("cpu 8086\nbits 16\nglobal _start\n_start:\n mov ax,msg\n hlt\nmsg:\n dw 0x1234\n")
def run(a): return subprocess.run(a,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
p=run(["x86-as","-f","bjobj",str(asm),"-o",str(b/"t.o")])
if p.returncode: print(p.stdout);raise SystemExit(1)
p=run([str(tool),str(b/"t.o")]);print(p.stdout,end="")
checks=["BJO1" in p.stdout,"ABS16" in p.stdout,"mov ax, 0x0004" in p.stdout]
print("PASS x86-objdump BJO1 metadata/relocation/disassembly" if all(checks) else "FAIL x86-objdump")
raise SystemExit(0 if all(checks) else 1)
