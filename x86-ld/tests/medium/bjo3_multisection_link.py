"""BJO3 linker integration: section placement and DS-relative DATA16."""
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[3]
assembler = root / 'x86-as' / 'x86-as.exe'
linker = root / 'x86-ld' / 'x86-ld.exe'
source = root / 'x86-as' / 'tests' / 'bjo3_multisection.asm'
with tempfile.TemporaryDirectory() as temp:
    obj = Path(temp) / 'multi.o'
    output = Path(temp) / 'multi.bin'
    subprocess.run([str(assembler), '-f', 'bjobj3', str(source), '-o', str(obj)], check=True)
    subprocess.run([str(linker), '-m', 'blackjack16', '-Ttext', '0x8000', str(obj), '-o', str(output)], check=True)
    data = output.read_bytes()
    assert data[:4] == bytes.fromhex('a10000c3'), data.hex()
    assert data[16:18] == bytes.fromhex('2a00'), data.hex()
    assert len(data) == 18, len(data)
    print('PASS BJO3 multi-section DATA16, DATA payload and BSS exclusion')
