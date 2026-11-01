cpu 8086
bits 16
org 0x1000
    lea dx, [bx+si+4]
    mov al, [bx]
    mov [bx+1], al
    mov dx, [bp+si+2]
    mov word [di], 0x1234
    push ax
    push di
    pop di
    pop ax
    hlt
