cpu 8086
bits 16
org 0x1000

inc ax
inc cx
inc al
inc byte [0x2000]
inc word [0x2002]
inc byte [bx + si + 5]
inc word [bp + 4]
hlt
