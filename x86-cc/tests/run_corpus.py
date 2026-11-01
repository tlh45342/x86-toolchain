import os
import subprocess
import sys
from collections import Counter
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
CC = os.environ.get("X86_CC", str(ROOT / ("x86-cc.exe" if os.name == "nt" else "x86-cc")))
CORPUS = Path(os.environ.get("C_TESTSUITE_ROOT", r"O:\src\c-testsuite-master\tests\single-exec"))
BUILD = HERE / "build" / "corpus"

def tags_for(src):
    p = Path(str(src) + ".tags")
    return set(p.read_text(errors="ignore").split()) if p.exists() else set()

def first_error(text):
    lines = [x.strip() for x in text.splitlines() if x.strip()]
    for line in reversed(lines):
        if "x86-cc: error:" in line:
            return line.split("x86-cc: error:", 1)[1].strip()
    return lines[-1] if lines else "unknown failure"

def main():
    if not CORPUS.is_dir():
        print("c-testsuite corpus not found:", CORPUS)
        print("Set C_TESTSUITE_ROOT to tests/single-exec.")
        return 2
    BUILD.mkdir(parents=True, exist_ok=True)
    sources = sorted(CORPUS.glob("*.c"))
    eligible = []
    skipped = Counter()
    for src in sources:
        tags = tags_for(src)
        blocked = tags & {"needs-libc", "needs-cpp"}
        if blocked:
            for tag in blocked:
                skipped[tag] += 1
            continue
        eligible.append((src, tags))

    passed = []
    failed = []
    standards = Counter()
    for src, tags in eligible:
        out = BUILD / (src.stem + ".asm")
        p = subprocess.run([CC, "-S", str(src), "-o", str(out)],
                           stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                           text=True)
        std = next((x for x in ("c89", "c99", "c11") if x in tags), "other")
        standards[(std, "pass" if p.returncode == 0 else "fail")] += 1
        if p.returncode == 0:
            passed.append(src.name)
        else:
            failed.append((src.name, first_error(p.stdout)))

    print("c-testsuite single-exec compile frontier")
    print("  corpus:   ", CORPUS)
    print("  total:    ", len(sources))
    print("  eligible: ", len(eligible))
    print("  pass:     ", len(passed))
    print("  fail:     ", len(failed))
    print("  skipped:  ", len(sources) - len(eligible))
    print("  skip reasons:", dict(skipped))
    print("  standards:", dict(standards))
    if failed:
        print("\nFirst 25 compile frontiers:")
        for name, why in failed[:25]:
            print(f"  {name}: {why}")
    return 0

if __name__ == "__main__":
    sys.exit(main())
