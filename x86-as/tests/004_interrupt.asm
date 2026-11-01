cpu 8086
bits 16
org 0x1000
    mov ax, 0x0E41
    int 0x10
    iret
