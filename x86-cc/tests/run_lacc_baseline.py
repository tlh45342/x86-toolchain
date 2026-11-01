"""Non-destructive LACC C89 compile-only baseline for x86-cc."""
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parent.parent
LACC = Path(sys.argv[1]) if len(sys.argv) > 1 else Path("O:/src/lacc-master")
CC = ROOT / "x86-cc.exe"
OUT = ROOT / "tests" / "build" / "lacc-baseline"
OUT.mkdir(parents=True, exist_ok=True)
CASES = (
    "self-referential-struct.c",
    "struct.c",
    "declarator-parens.c",
    "typedef.c",
    "pointer.c",
    "array-reverse-index.c",
)
passed = 0
for name in CASES:
    source = LACC / "test" / "c89" / name
    if not source.is_file():
        print("MISSING", source)
        continue
    dest = OUT / (source.stem + ".o")
    proc = subprocess.run([str(CC), "-c", str(source), "-o", str(dest)],
                          capture_output=True, text=True, cwd=str(ROOT))
    (OUT / (source.stem + ".log")).write_text(proc.stdout + proc.stderr,
                                              encoding="utf-8")
    status = "COMPILE-PASS" if proc.returncode == 0 else "COMPILE-FAIL"
    print(status, name)
    if proc.returncode == 0:
        passed += 1
print("Compile-only baseline: %d/%d passed" % (passed, len(CASES)))
