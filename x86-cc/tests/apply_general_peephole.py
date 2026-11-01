from pathlib import Path
p=Path(r'O:\x86\toolchain\x86-cc\x86-cc.c')
s=p.read_text()
start=s.index('/* Sprint 10: deliberately narrow')
end=s.index('static void usage(FILE *f)',start)
s=s[:start]+'#include "peephole.h"\n\n'+s[end:]
s=s.replace('peephole_dead_ax_address(output)','peephole_optimize_file(output, g_optimization_level)')
s=s.replace('peephole_dead_ax_address(tmp_path)','peephole_optimize_file(tmp_path, g_optimization_level)')
p.write_text(s)
print('REPLACED',end-start)
