#!/usr/bin/env python3
"""Persist x86-cc checkout-local installation settings in config.mk."""
from pathlib import Path
import sys

ALLOWED = ("PREFIX", "BINDIR", "LIBDIR", "INCLUDEDIR")

def main(argv):
    if len(argv) < 2:
        print("usage: config-set.py CONFIG [NAME=VALUE ...]", file=sys.stderr)
        return 2
    path = Path(argv[1])
    values = {}
    if path.exists():
        for raw in path.read_text(encoding="utf-8").splitlines():
            if "=" in raw and not raw.lstrip().startswith("#"):
                k, v = raw.split("=", 1)
                k, v = k.strip().upper(), v.strip()
                if k in ALLOWED:
                    values[k] = v
    for arg in argv[2:]:
        if "=" not in arg:
            print(f"config-set: expected NAME=VALUE, got {arg!r}", file=sys.stderr)
            return 2
        k, v = arg.split("=", 1)
        k, v = k.strip().upper(), v.strip()
        if k not in ALLOWED:
            print(f"config-set: unknown setting {k}", file=sys.stderr)
            return 2
        if not v:
            print(f"config-set: {k} may not be empty", file=sys.stderr)
            return 2
        values[k] = v
    missing = [k for k in ALLOWED if k not in values]
    if missing:
        print("config-set: missing effective setting(s): " + ", ".join(missing), file=sys.stderr)
        return 2
    path.write_text("".join(f"{k} := {values[k]}\n" for k in ALLOWED), encoding="ascii")
    print(f"Updated {path}")
    for k in ALLOWED:
        print(f"  {k}={values[k]}")
    return 0

if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
