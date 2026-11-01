cpu 8086
bits 16
org 0x1000
mov ax, 0x8001
cwd
mov al, 0x7f
inc al
dec al
xor al, 0x55
xor ax, 0x1234
xor bx, ax
test al, 0x0f
mov word [0x2000], 0xBEEF
push word [0x2000]
pop word [0x2002]
mov ax, 0
mov es, ax
mov byte [0x2010], 0x11
mov byte [0x2011], 0x22
mov byte [0x2012], 0x42
mov di, 0x2010
mov cx, 3
mov al, 0x42
repne scasb
cmp ax, ax
jle short jle_ok
mov si, 0xDEAD
jle_ok:
ja short bad
mov si, 0xBEEF
bad:
hlt
