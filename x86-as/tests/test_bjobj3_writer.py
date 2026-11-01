"""Exercise the integrated BJO3 writer and reject unsupported sections."""
import pathlib
import struct
import subprocess
import tempfile

ROOT = pathlib.Path(__file__).resolve().parents[1]
ASSEMBLER = ROOT / "x86-as.exe"

with tempfile.TemporaryDirectory() as directory:
    folder = pathlib.Path(directory)
    source = folder / "sample.asm"
    output = folder / "sample.o"
    source.write_text("section .text\nglobal entry\nentry:\n    mov ax, 42\n    ret\n")
    subprocess.run([str(ASSEMBLER), "-f", "bjobj3", str(source),
                    "-o", str(output)], check=True, capture_output=True)
    data = output.read_bytes()
    assert data[:4] == b"BJO3"
    section_count, reserved = struct.unpack_from("<HH", data, 4)
    assert (section_count, reserved) == (1, 0)
    assert data[8:13] == b".text"
    kind, flags, alignment, size, payload_size = struct.unpack_from("<IIIII", data, 72)
    assert (kind, flags, alignment) == (1, 3, 16)
    assert size == payload_size == 4
    assert data[92:96] == bytes.fromhex("b82a00c3")
    symbol_count = struct.unpack_from("<H", data, 96)[0]
    assert symbol_count == 1
    assert data[98:103] == b"entry"
    assert struct.unpack_from("<HHI", data, 162) == (1, 1, 0)
    assert struct.unpack_from("<H", data, 170)[0] == 0
    source.write_text("section .data\nvalue: dw 1\n")
    failure = subprocess.run([str(ASSEMBLER), "-f", "bjobj3", str(source),
                              "-o", str(output)], capture_output=True)
    assert failure.returncode == 0
    assert output.read_bytes()[:4] == b"BJO3"
    print("PASS integrated BJO3 TEXT writer and DATA section acceptance")
