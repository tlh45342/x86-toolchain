from pathlib import Path
p=Path(r"O:\x86\toolchain\x86-cc\x86-cc.c")
s=p.read_text()
old="""    { char *p = src;
      while (*p) {
        if (!strncmp(p, "extern", 6) && !(isalnum((unsigned char)p[6]) || p[6]=='_') && (p==src || !(isalnum((unsigned char)p[-1]) || p[-1]=='_'))) memset(p, ' ', 6);
        p++;
      }
    }
"""
assert old in s
s=s.replace(old,"",1)
p.write_text(s)
print("preserved extern through semantic passes")
