import os
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
BUILD = HERE / "build"
BUILD.mkdir(exist_ok=True)
CC = ROOT / ("x86-cc.exe" if os.name == "nt" else "x86-cc")
SRC = HERE / "inline_asm_block.c"
ASM = BUILD / "inline_asm_block.asm"
OBJ = BUILD / "inline_asm_block.o"

def run(args):
    p = subprocess.run([str(x) for x in args], stdout=subprocess.PIPE,
                       stderr=subprocess.STDOUT, text=True)
    if p.returncode:
        print(p.stdout)
        sys.exit(p.returncode)
    return p.stdout

run([CC, "--blackjack", "-S", SRC, "-o", ASM])
text = ASM.read_text()
ordered = ["cli", "xor ax, ax", "mov ds, ax", "mov es, ax", "sti"]
pos = -1
for insn in ordered:
    pos = text.find(insn, pos + 1)
    if pos < 0:
        print("FAIL inline asm emission:", insn)
        sys.exit(1)

run(["x86-as", "-f", "bjobj", ASM, "-o", OBJ])
print("PASS x86-cc asm { } preserves and assembles ordered x86 source")
