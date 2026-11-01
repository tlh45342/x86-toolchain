from pathlib import Path
p=Path(__file__).resolve().parent.parent/'x86-cc.c'
s=p.read_text()
s=s.replace('#include "peephole.h"','#include "peephole.h"\n#include "long_branches.h"')
s=s.replace('if (!peephole_optimize_file(output, g_optimization_level)) goto done;','if (!peephole_optimize_file(output, g_optimization_level)) goto done;\n        if (!x86cc_expand_conditional_branches(output)) goto done;')
s=s.replace('if (!peephole_optimize_file(tmp_path, g_optimization_level)) goto done;','if (!peephole_optimize_file(tmp_path, g_optimization_level)) goto done;\n    if (!x86cc_expand_conditional_branches(tmp_path)) goto done;')
p.write_text(s)
p=Path(__file__).resolve().parent.parent/'Makefile'
s=p.read_text().replace('x86-cc.c peephole.h','x86-cc.c peephole.h long_branches.h')
p.write_text(s)
print('wired 8086 long conditional branches')
