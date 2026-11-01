cpu 8086
bits 16
org 0x1000
    mov ax, 0xB800
    mov es, ax
    mov ax, es
    hlt
