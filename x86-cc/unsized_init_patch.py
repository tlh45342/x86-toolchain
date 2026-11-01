from pathlib import Path
p=Path(r"O:\x86\toolchain\x86-cc\x86-cc.c")
s=p.read_text()
old="""                if (*q==']') {
                    if (!is_extern_decl) { fprintf(stderr,"x86-cc: global: incomplete array requires extern near %s [decl %.80s]\\n",name,p); return 0; }
                    q++; array_len=-1;
                } else {"""
new="""                if (*q==']') {
                    q++; array_len=-1; /* extern incomplete, or definition completed by initializer */
                } else {"""
assert old in s
s=s.replace(old,new,1)
old="""            if (*q=='=') {
                char *ep; if(array_len || ptr || type_width > 2) { fprintf(stderr,"x86-cc: global: initializer not yet supported for %s near %.120s\\n",name,q); return 0; }"""
new="""            if (array_len < 0 && *q!='=' && !is_extern_decl) {
                fprintf(stderr,"x86-cc: global: incomplete array definition requires initializer near %s\\n",name); return 0;
            }
            if (*q=='=') {
                char *ep; if(array_len || ptr || type_width > 2) { fprintf(stderr,"x86-cc: global: initializer not yet supported for %s near %.120s\\n",name,q); return 0; }"""
assert old in s
s=s.replace(old,new,1)
p.write_text(s)
print("accepted initializer-completed unsized arrays; initializer semantics still explicit frontier")
