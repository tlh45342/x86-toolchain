cpu 8086
bits 16
global _start
_start:
 mov ax,msg
 hlt
msg:
 dw 0x1234
