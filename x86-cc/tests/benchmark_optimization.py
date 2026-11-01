"""Measure 8086 executed instructions from x86-run extended trace.
Wall time is host end-to-end including VM startup, NOT guest CPU time.
"""
import csv
import os
import re
import subprocess
import tempfile
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
HERE = ROOT / 'tests'
CC = ROOT / ('x86-cc.exe' if os.name == 'nt' else 'x86-cc')
VM = os.environ.get('X86_RUN', 'x86-run')
CASES = ('return42','struct_basic','struct_typed_layout','if_true',
         'if_else_blocks','long_if_body','logical_and_true','logical_or_false',
         'runtime_mul_locals','array_loop','large_local_array')
TRACE = re.compile(r'^\s*[0-9A-Fa-f]{4}:[0-9A-Fa-f]{4}\s+[0-9A-Fa-f]{2}(?:\s|$)')

def execute(args, **kw):
    t = time.perf_counter()
    p = subprocess.run(args, cwd=ROOT, text=True, capture_output=True, **kw)
    elapsed = (time.perf_counter()-t)*1000
    if p.returncode:
        raise RuntimeError(f'{args}: {p.stdout} {p.stderr}')
    return elapsed

def main():
    template = (HERE/'test.script.in').read_text()
    rows=[]
    with tempfile.TemporaryDirectory(prefix='x86cc-bench-') as td:
        directory=Path(td)
        for stem in CASES:
            for level in ('O0','O1'):
                binary=directory/f'{stem}-{level}.bin'
                log=directory/f'{stem}-{level}.log'
                execute([str(CC),'-'+level,str(HERE/(stem+'.c')),'-o',str(binary)])
                script=template.replace('@BIN@',str(binary)).replace('@LOG@',str(log))
                elapsed=execute([VM],input=script)
                contents=log.read_text()
                count=sum(bool(TRACE.match(line)) for line in contents.splitlines())
                if not count or 'hlt' not in contents.lower():
                    raise RuntimeError(f'{stem} {level}: missing execution trace/HLT')
                rows.append((stem,level,binary.stat().st_size,count,round(elapsed,2)))
    out=HERE/'optimization-benchmark.csv'
    with out.open('w',newline='') as f:
        writer=csv.writer(f)
        writer.writerow(('sample','level','binary_bytes','trace_instructions','host_vm_ms'))
        writer.writerows(rows)
    print('sample,level,binary_bytes,trace_instructions,host_vm_ms')
    for row in rows: print(','.join(map(str,row)))
    print('PASS measured',len(rows),'executions; host timings include VM startup')

if __name__=='__main__': main()
