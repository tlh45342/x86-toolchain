"""Regression for BJO2 inspection and far-call decoding."""
import pathlib
import subprocess
import sys

exe = pathlib.Path(sys.argv[1]).resolve()
obj = pathlib.Path(sys.argv[2]).resolve()
result = subprocess.run([str(exe), str(obj)], capture_output=True, text=True)
assert result.returncode == 0, result.stderr
for expected in ("BJO2", "[1] .text size=6 align=16", "_start",
                 ".text 0001 FAR32", "call far 0x0000:0x0000"):
    assert expected in result.stdout, (expected, result.stdout)
print("PASS BJO2 section/symbol/relocation inspection")
print("PASS far CALL immediate disassembly")
