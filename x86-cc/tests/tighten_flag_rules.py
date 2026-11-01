from pathlib import Path
p=Path(__file__).resolve().parent.parent/'peephole.h'
s=p.read_text()
a=s.index('    static const char *const ops[] = {')
b=s.index('    };',a)+len('    };')
s=s[:a]+'    static const char *const ops[] = {"cmp","test","add","sub","and","or","xor",NULL};'+s[b:]
p.write_text(s)
print('Limited flag kill to full arithmetic flag overwrites')
