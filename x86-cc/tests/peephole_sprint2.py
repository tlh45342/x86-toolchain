"""Conservative 8086 peephole prototype. No modifications to original input.

Removes dead AX address construction only if the following MOV overwrites AX
and the flags set by SUB/ADD are dead before any possible flag read.
"""
import re
import sys
from pathlib import Path

ARITH = re.compile(r'\s*(?:add|sub) ax, (?:\d+|bx)\s*$', re.I)
OVERWRITE = re.compile(r'\s*mov ax, (?:\[bp[+-]\d+\]|0x[0-9a-f]+|\d+)\s*$', re.I)
FLAG_WRITER = re.compile(r'\s*(?:cmp|test|add|sub|and|or|xor|inc|dec|shl|shr)\b', re.I)
FLAG_READER = re.compile(r'\s*(?:j(?:[a-z]+)|loop[a-z]*|adc|sbb|rcl|rcr|pushf|lahf|into)\b', re.I)
BARRIER = re.compile(r'^\s*(?:[.;]|[\w.$]+:|ret\b|call\b|hlt\b|int\b|popf\b|sahf\b)', re.I)

def flags_dead(lines, start):
    for line in lines[start:]:
        s = line.strip()
        if not s or s.startswith(';'):
            continue
        if BARRIER.match(s) or FLAG_READER.match(s):
            return False
        if FLAG_WRITER.match(s):
            return True
    return False

def optimize(source):
    lines = source.splitlines(keepends=True)
    output = []
    removed = 0
    i = 0
    while i < len(lines):
        if (i+2 < len(lines) and lines[i].strip() == 'mov ax, bp'
            and ARITH.fullmatch(lines[i+1].strip())
            and OVERWRITE.fullmatch(lines[i+2].strip())
            and flags_dead(lines, i+3)):
            output.append(lines[i+2]); i += 3; removed += 2
        else:
            output.append(lines[i]); i += 1
    return ''.join(output), removed

if __name__ == '__main__':
    if len(sys.argv) != 3:
        sys.exit('usage: peephole_sprint2.py INPUT.asm OUTPUT.asm')
    source = Path(sys.argv[1]).read_text()
    result, count = optimize(source)
    Path(sys.argv[2]).write_text(result)
    print(f'peephole: removed {count} instructions')
