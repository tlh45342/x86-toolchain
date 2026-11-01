from pathlib import Path
p=Path(__file__).with_name("x86-cc.c")
s=p.read_text()
old='} else if (end-line >= 8 && !strncmp(line, "typedef ", 8)) {\n            char tline[256], alias[64]; size_t z = (size_t)(end-line);'
new='''} else if ((end-line >= 8 && !strncmp(line, "typedef ", 8)) ||
                   (end-line >= 9 && strstr(line, " typedef ") &&
                    strstr(line, " typedef ") < end)) {
            char tline[256], alias[64]; size_t z = (size_t)(end-line);'''
assert old in s
s=s.replace(old,new,1)
old2='''            memcpy(tline, line, z); tline[z]=0;
            { char *fp=strstr(tline,"(*"); char stag[64];'''
new2='''            memcpy(tline, line, z); tline[z]=0;
            /* C permits typedef among declaration specifiers, not just first.
             * Canonicalize its position before the compact alias scanner.
             * Preserve the rest of the declaration for existing validation. */
            if (strncmp(tline, "typedef ", 8)) {
                char *kw = strstr(tline, " typedef ");
                if (kw) {
                    char reordered[256];
                    size_t prefix = (size_t)(kw-tline);
                    int n = snprintf(reordered,sizeof(reordered),
                                     "typedef %.*s %s", (int)prefix,tline,kw+9);
                    if (n < 0 || (size_t)n >= sizeof(reordered)) { free(out); return 0; }
                    strcpy(tline,reordered);
                }
            }
            { char *fp=strstr(tline,"(*"); char stag[64];'''
assert old2 in s
s=s.replace(old2,new2,1)
p.write_text(s)
print('patched typedef specifier ordering')
