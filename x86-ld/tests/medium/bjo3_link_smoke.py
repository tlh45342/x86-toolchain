"""Verify x86-as BJO3 objects can be linked by x86-ld."""
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[3]
assembler = root / "x86-as" / "x86-as.exe"
linker = root / "x86-ld" / "x86-ld.exe"
with tempfile.TemporaryDirectory() as directory:
    folder = Path(directory)
    objects = []
    for index, source in enumerate((
        "section .text\nglobal entry\nentry:\n mov ax, 42\n ret\n",
        "section .text\nglobal helper\nhelper:\n mov ax, 7\n ret\n",
    )):
        asm = folder / f"part{index}.asm"
        obj = folder / f"part{index}.o"
        asm.write_text(source)
        subprocess.run([str(assembler), "-f", "bjobj3", str(asm), "-o", str(obj)],
                       check=True, capture_output=True)
        objects.append(obj)
    output = folder / "linked.bin"
    subprocess.run([str(linker), "-m", "blackjack16", "-Ttext", "0x8000",
                    *(str(obj) for obj in objects), "-o", str(output)],
                   check=True, capture_output=True)
    assert output.read_bytes() == bytes.fromhex("b82a00c3b80700c3")
    print("PASS BJO3 assembler-to-linker two-object TEXT pipeline")
