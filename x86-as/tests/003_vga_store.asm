cpu 8086
bits 16
org 0x1000
    mov ax, 0xB800
    mov es, ax
    mov di, 0
    mov ax, 0x0748
    mov [es:di], ax
    mov ax, 0x0769
    mov [es:di+2], ax
    hlt
