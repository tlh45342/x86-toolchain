"""Validate BJO2 object inspection against good and malformed inputs."""
import pathlib
import struct
import subprocess
import sys
import tempfile

objdump = pathlib.Path(sys.argv[1]).resolve()


def inspect(path):
    return subprocess.run([str(objdump), str(path)], capture_output=True, text=True)


def object_bytes(section=1, alignment=16, symbol_section=1, relocation_section=1):
    header = b"BJO2" + struct.pack("<HHHHHIH", 1, 2, 1, 0, section, 6, alignment)
    origin = b"__bjo_origin".ljust(64, b"\0") + struct.pack("<HIB", 1, 0, 1)
    start = b"_start".ljust(64, b"\0") + struct.pack("<HIB", symbol_section, 0, 1)
    reloc = b"answer".ljust(64, b"\0") + struct.pack("<HIB", relocation_section, 1, 3)
    return header + origin + start + reloc + b"\x9a\0\0\0\0\xf4"


with tempfile.TemporaryDirectory() as temporary:
    path = pathlib.Path(temporary) / "sample.o"
    path.write_bytes(object_bytes())
    result = inspect(path)
    assert result.returncode == 0, result.stderr
    for expected in ("BJO2", ".text size=6 align=16", "_start",
                     ".text 0001 FAR32", "call far 0x0000:0x0000"):
        assert expected in result.stdout, (expected, result.stdout)
    print("PASS BJO2 metadata and far-call disassembly")

    for label, content in (
        ("truncated", object_bytes()[:-1]),
        ("unsupported section", object_bytes(section=2)),
        ("invalid symbol section", object_bytes(symbol_section=3)),
        ("invalid relocation section", object_bytes(relocation_section=2)),
    ):
        path.write_bytes(content)
        result = inspect(path)
        assert result.returncode != 0, (label, result.stdout)
        print(f"PASS BJO2 rejects {label}")
