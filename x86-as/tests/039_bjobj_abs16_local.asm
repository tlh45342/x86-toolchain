bits 16
global _start
_start:
    mov ax,[word_value]
    mov [word_value],ax
    mov al,[byte_value]
    mov [byte_value],al
    mov bx,[word_value]
    mov [word_value],bx
    mov es,[word_value]
    mov [word_value],es
    mov ax,[word_value+2]
    mov [word_value+2],ax
    hlt
byte_value: db 0
word_value: dw 0
             dw 0
