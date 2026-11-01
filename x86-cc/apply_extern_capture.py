from pathlib import Path
p=Path(r"O:\x86\toolchain\x86-cc\x86-cc.c")
s=p.read_text()
old="""        { int is_extern_decl=0;
        while ((!strncmp(q,"static",6) && isspace((unsigned char)q[6])) ||"""
new="""        { int is_extern_decl=0;
        if (!strncmp(q,"extern",6) && isspace((unsigned char)q[6])) is_extern_decl=1;
        while ((!strncmp(q,"static",6) && isspace((unsigned char)q[6])) ||"""
assert old in s
s=s.replace(old,new,1)
p.write_text(s)
print("extern capture hardened")
