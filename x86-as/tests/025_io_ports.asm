cpu 8086
bits 16
org 0
in al, 0x80
in ax, 0x80
out 0x80, al
out 0x80, ax
in al, dx
in ax, dx
out dx, al
out dx, ax
