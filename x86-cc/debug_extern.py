from pathlib import Path
p=Path(r"O:\x86\toolchain\x86-cc\x86-cc.c")
s=p.read_text()
old='if (!is_extern_decl) { fprintf(stderr,"x86-cc: global: incomplete array requires extern near %s\\n",name); return 0; }'
new='if (!is_extern_decl) { fprintf(stderr,"x86-cc: global: incomplete array requires extern near %s [decl %.80s]\\n",name,p); return 0; }'
assert old in s
p.write_text(s.replace(old,new,1))
