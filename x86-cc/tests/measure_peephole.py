from pathlib import Path
from peephole_sprint2 import optimize
files = list(Path('tests/build').glob('*.asm'))
changed = removed = 0
for f in files:
    src = f.read_text(errors='replace')
    dst, n = optimize(src)
    removed += n
    changed += bool(n)
print('assembly files:', len(files))
print('files changed:', changed)
print('instructions removed:', removed)
