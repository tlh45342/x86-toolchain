cpu 8086
bits 16
org 0x1000
start:
    cmp al, 0
    jnz short faraway
times 200 db 0
faraway:
    hlt
