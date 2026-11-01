bits 16
org 0x1000

; 8086 INC/DEC family: register and r/m8,r/m16 encodings.
inc ax
inc cx
dec ax
dec di
inc al
dec al
inc byte [0x2000]
dec byte [0x2001]
inc word [0x2002]
dec word [0x2004]
inc byte [bx + si + 5]
dec byte [bx + si + 6]
inc word [bp + 4]
dec word [bp + 6]
hlt
