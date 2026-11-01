cpu 8086
bits 16
org 0x1000
    mov ax, 1
    add ax, 2
    sub ax, 1
    xor bx, bx
    or ax, bx
    hlt
