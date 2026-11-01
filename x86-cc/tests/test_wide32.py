"""Blackjack 32-bit arithmetic compiler regression tests.

Run: python tests/test_wide32.py
Each case is compiled independently to distinguish parser/codegen failures.
Output is generated in tests/build/wide32, never alongside source files.
"""
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TESTS = Path(__file__).resolve().parent
BUILD = TESTS / "build" / "wide32"
CASES = ("literal", "decimal", "suffix", "hex", "xor", "multiply", "shift", "promotion", "bj1")


def main():
    BUILD.mkdir(parents=True, exist_ok=True)
    failures = 0
    for case in CASES:
        source = TESTS / ("wide32_" + case + ".c")
        output = BUILD / (case + ".asm")
        result = subprocess.run(
            [str(ROOT / "x86-cc.exe"), "-S", str(source), "-o", str(output)],
            capture_output=True, text=True,
        )
        if result.returncode:
            failures += 1
            print("FAIL", case, "compile")
            print((result.stderr or result.stdout).strip())
        elif not output.exists() or output.stat().st_size == 0:
            failures += 1
            print("FAIL", case, "assembly missing")
        else:
            print("PASS", case, "compile (execution NOT validated)")
    print(f"wide32 compile: {len(CASES) - failures}/{len(CASES)} passed")
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
