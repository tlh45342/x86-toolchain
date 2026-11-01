cpu 8086
bits 16
org 0x1000
    jmp ax
    jmp bx
    jmp si
    jmp word [bp+0x5A]
