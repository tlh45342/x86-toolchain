"""Regression: medium FAR32 must retain the target object's CS base."""
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[3]
assembler = root / 'x86-as' / 'x86-as.exe'
linker = root / 'x86-ld' / 'x86-ld.exe'

with tempfile.TemporaryDirectory() as temp:
    folder = Path(temp)
    sources = (
        'section .text\nglobal caller\nextern callee\ncaller:\n call far callee\n retf\n',
        'section .text\n' + ' nop\n' * 35 + 'global callee\ncallee:\n retf\n',
    )
    objects = []
    for index, source in enumerate(sources):
        asm = folder / f'part{index}.asm'
        obj = folder / f'part{index}.o'
        asm.write_text(source)
        subprocess.run([str(assembler), '-f', 'bjobj3', str(asm), '-o', str(obj)],
                       check=True, capture_output=True)
        objects.append(obj)
    output = folder / 'linked.bin'
    command = [str(linker), '-m', 'blackjack16-medium', '-Ttext', '0x8000',
               *(str(obj) for obj in objects), '-o', str(output)]
    subprocess.run(command, check=True, capture_output=True)
    image = output.read_bytes()
    # caller is 6 bytes, so target object begins at aligned output offset 0x10.
    assert image[:5] == bytes.fromhex('9a23000108'), image[:5].hex()
    bad = command.copy()
    bad[bad.index('0x8000')] = '0x8001'
    result = subprocess.run(bad, capture_output=True, text=True)
    assert result.returncode != 0, 'unaligned medium base was accepted'
    assert 'paragraph-aligned' in result.stderr, result.stderr
    print('PASS medium FAR32 object CS, 16-bit offset, unaligned base rejection')
