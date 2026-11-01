cpu 8086
bits 16
org 0x7C00
%macro TTY 1
    mov ax, (0x0E00 | %1)
    int 0x10
%endmacro
start:
    TTY 'O'
    TTY 'K'
    hlt
