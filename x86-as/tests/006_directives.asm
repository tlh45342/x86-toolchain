cpu 8086
bits 16
org 0x7C00
start:
    db "X86", 13, 10
    dw 0x1234
times 16-($-$$) db 0
    dw 0xAA55
