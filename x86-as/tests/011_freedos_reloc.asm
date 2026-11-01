cpu 8086
bits 16
org 0x1000
start:
    cli
    cld
    xor ax, ax
    mov cx, 3
    rep movsw
    std
    movsb
    sti
    hlt
