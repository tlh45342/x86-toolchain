cpu 8086
bits 16
org 0x1000
start:
    mov ax, 0xBEEF
    mov bx, 0x1234
    hlt
