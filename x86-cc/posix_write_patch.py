from pathlib import Path
p=Path(r"O:\x86\toolchain\x86-cc\x86-cc.c")
s=p.read_text()
needle='!strcmp(name, "bj_write") || '
assert needle in s
s=s.replace(needle,'!strcmp(name, "write") || !strcmp(name, "bj_write") || ',1)
needle='fprintf(out, "; Blackjack userspace runtime\\n");\n        fprintf(out, "bj_write:'
assert needle in s
insert='''fprintf(out, "; Blackjack userspace runtime\\n");
        fprintf(out, "write:\\n    push bp\\n    mov bp, sp\\n    mov bx, [bp+8]\\n    mov si, [bp+6]\\n    mov cx, [bp+4]\\n    mov ax, 1\\n    int 0x60\\n    mov sp, bp\\n    pop bp\\n    ret\\n\\n");
        /* Legacy string helper.  New userspace must use POSIX write(fd,buf,count). */
        fprintf(out, "bj_write:'''
s=s.replace(needle,insert,1)
p.write_text(s)
print("added POSIX write runtime entry; bj_write retained only as legacy helper")
