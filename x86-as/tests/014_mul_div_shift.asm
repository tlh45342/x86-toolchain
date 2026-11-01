cpu 8086
bits 16
org 0x1000
mov ax, 0x0010
mov bx, 0x0003
mul bx
shr ax, 1
mov cx, 2
shr dx, cl
mul word [bp+0x16]
div bx
shr word [bp+0x10], cl
hlt
