bits 16
section .text
global entry
entry:
    mov ax, [counter]
    ret
section .data
global counter
counter:
    dw 42
section .bss
global scratch
scratch:
    resb 32
