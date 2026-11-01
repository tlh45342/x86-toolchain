from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[3]
with tempfile.TemporaryDirectory() as tmp:
    folder = Path(tmp)
    sources = (
        'section .text\nglobal entry\nextern helper\nentry:\n call far helper\n ret\n',
        'section .text\nglobal helper\nhelper:\n mov ax, 42\n retf\n',
    )
    objects = []
    for index, source in enumerate(sources):
        asm = folder / f'{index}.asm'
        obj = folder / f'{index}.o'
        asm.write_text(source)
        subprocess.run([str(root / 'x86-as' / 'x86-as.exe'), '-f', 'bjobj3', str(asm), '-o', str(obj)], check=True)
        objects.append(str(obj))
    output = folder / 'linked.bin'
    subprocess.run([str(root / 'x86-ld' / 'x86-ld.exe'), '-m', 'blackjack16', '-Ttext', '0x8000', *objects, '-o', str(output)], check=True)
    data = output.read_bytes()
    assert data[0] == 0x9a and data[6:9] == bytes.fromhex('b82a00'), data.hex()
    print('PASS BJO3 cross-object FAR32 relocation')
