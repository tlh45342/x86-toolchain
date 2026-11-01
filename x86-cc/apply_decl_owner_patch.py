from pathlib import Path
p=Path(r"O:\x86\toolchain\x86-cc\x86-cc.c")
s=p.read_text()
old="""        } else { p++; continue; }
        while (isspace((unsigned char)*q)) q++;"""
new="""        } else { p++; continue; }
        /* Once a declaration prefix was recognized, this pass owns it.
         * Do not let the outer character scanner rediscover the same
         * declaration after its storage-class specifier. */
        while (isspace((unsigned char)*q)) q++;"""
assert old in s
s=s.replace(old,new,1)
p.write_text(s)
print("declaration ownership marker applied")
