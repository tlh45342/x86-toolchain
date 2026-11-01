org 0x8000
    mov si, target
    mov ax, [bx+target]
target:
    db 'TARGET',0
