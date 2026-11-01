"""BJO2 section syntax regression: accept TEXT, reject DATA/BSS until implemented."""
import pathlib
import subprocess
import sys
import tempfile

assembler = pathlib.Path(sys.argv[1])
with tempfile.TemporaryDirectory() as directory:
    root = pathlib.Path(directory)
    for section, expected_success in ((".text", True), (".data", False), (".bss", False)):
        source = root / "section.asm"
        output = root / "section.o"
        source.write_text(f"section {section}\nstart:\n    nop\n")
        result = subprocess.run([str(assembler), "-f", "bjobj2", str(source), "-o", str(output)],
                                capture_output=True, text=True)
        if (result.returncode == 0) != expected_success:
            print(result.stdout, result.stderr)
            raise SystemExit(f"FAIL BJO2 section {section}")
        if expected_success and output.read_bytes()[:4] != b"BJO2":
            raise SystemExit("FAIL BJO2 magic")
        if not expected_success and "not yet supported" not in result.stderr:
            raise SystemExit(f"FAIL BJO2 missing diagnostic for {section}")
        print(f"PASS BJO2 section {section} {'accepted' if expected_success else 'rejected safely'}")
