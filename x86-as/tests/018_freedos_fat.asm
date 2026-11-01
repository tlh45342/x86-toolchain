cpu 8086
bits 16
org 0x1000
    cmp byte [es:di], 0
    and ah, 0x0F
    and di, 0x00FF
    or ax, ax
    jnc short okay
okay:
    push ds
    pop es
    push cs
    pop ds
    jmp far [bp+0x5A]
