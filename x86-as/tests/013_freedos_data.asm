cpu 8086
bits 16
org 0x1000
    mov [bp-0x3a], ds
    mov ds, [bp-0x3a]
    mov byte [bx+si+2], 0x7f
    add ax, [bx]
    add [bx+2], dx
    adc ax, [bx]
    adc [bx+2], dx
    cbw
