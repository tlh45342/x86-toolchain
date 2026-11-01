from pathlib import Path
import subprocess
import sys

here = Path(__file__).resolve().parent
root = here.parent
compiler = root / ("x86-cc.exe" if sys.platform == "win32" else "x86-cc")
source = here / "far_pointer_local.c"
assembly = here / "far_pointer_local.regression.asm"
obj = here / "far_pointer_local.regression.o"

compile_asm = subprocess.run(
    [str(compiler), "-S", str(source), "-o", str(assembly)],
    stdout=subprocess.PIPE,
    stderr=subprocess.STDOUT,
    text=True,
)

if compile_asm.returncode != 0:
    print(compile_asm.stdout, end="")
    print("FAIL local far-pointer assembly generation")
    sys.exit(1)

text = assembly.read_text(encoding="utf-8")
required = (
    "mov [bp-4], ax",
    "mov [bp-2], dx",
    "mov es, dx",
    "mov al, [es:bx]",
)

if not all(instruction in text for instruction in required):
    print("FAIL local far-pointer segment:offset code generation")
    sys.exit(1)

compile_obj = subprocess.run(
    [str(compiler), "-c", str(source), "-o", str(obj)],
    stdout=subprocess.PIPE,
    stderr=subprocess.STDOUT,
    text=True,
)

if compile_obj.returncode != 0:
    print(compile_obj.stdout, end="")
    print("FAIL local far-pointer object generation")
    sys.exit(1)

global_source = here / "far_index_rvalue.c"
global_assembly = here / "far_index_rvalue.regression.asm"
compile_global = subprocess.run(
    [str(compiler), "-S", str(global_source), "-o", str(global_assembly)],
    stdout=subprocess.PIPE,
    stderr=subprocess.STDOUT,
    text=True,
)
if compile_global.returncode != 0:
    print(compile_global.stdout, end="")
    print("FAIL global indexed far-pointer assembly generation")
    sys.exit(1)

global_text = global_assembly.read_text(encoding="utf-8")
if "mov ax, [es:bx]" not in global_text or "mov [es:bx], ax" not in global_text:
    print("FAIL global indexed far-pointer rvalue/store code generation")
    sys.exit(1)

print("PASS x86-cc function-local and global indexed far pointers")
