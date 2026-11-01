"""Permanent BJO3 object inspection regression tests."""
from pathlib import Path
import os
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
tool = root / ("x86-objdump.exe" if os.name == "nt" else "x86-objdump")
assembler = root.parent / "x86-as" / ("x86-as.exe" if os.name == "nt" else "x86-as")

def run(*args):
    return subprocess.run([str(arg) for arg in args],
                          capture_output=True, text=True)

with tempfile.TemporaryDirectory() as directory:
    folder = Path(directory)
    source = root.parent / "x86-as" / "tests" / "bjo3_multisection.asm"
    obj = folder / "sections.o"
    assembled = run(assembler, "-f", "bjobj3", source, "-o", obj)
    assert assembled.returncode == 0, assembled.stderr
    result = run(tool, obj)
    assert result.returncode == 0, result.stderr
    output = result.stdout
    for expected in ("BJO3", ".text", ".data", ".bss",
                     "size=32 payload=0", "DATA16", "symbol[1]",
                     "EXECUTABLE SECTION .text", "mov ax, [0x0000]"):
        assert expected in output, (expected, output)
    assert "flat binary" not in output
    assert "inc dx" not in output

    # A malformed section payload must not silently become machine code.
    broken = bytearray(obj.read_bytes())
    broken[8 + 80:8 + 84] = (0xffffffff).to_bytes(4, "little")
    bad = folder / "truncated.o"
    bad.write_bytes(broken)
    rejected = run(tool, bad)
    assert rejected.returncode != 0, rejected.stdout
    assert "malformed BJO3" in rejected.stderr, rejected.stderr

    # Preserve the flat-binary fallback for actual raw code.
    binary = folder / "raw.bin"
    binary.write_bytes(bytes.fromhex("b82a00c3"))
    raw = run(tool, binary)
    assert raw.returncode == 0
    assert "flat binary" in raw.stdout
    assert "mov ax, 0x002A" in raw.stdout

print("PASS BJO3 sections, data/BSS, relocation, disassembly, malformed rejection, flat fallback")
