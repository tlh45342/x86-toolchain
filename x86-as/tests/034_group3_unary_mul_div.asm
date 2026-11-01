cpu 8086
bits 16
org 0x1000

; /0 TEST immediate -- non-accumulator register plus memory, byte and word
test bl, 0x12
test bx, 0x1234
test byte [bx+si+4], 0x56
test word [bx+si+4], 0x5678

; /2 NOT
not bl
not bx
not byte [bx+si+4]
not word [bx+si+4]

; /3 NEG
neg bl
neg bx
neg byte [bx+si+4]
neg word [bx+si+4]

; /4 MUL
mul bl
mul bx
mul byte [bx+si+4]
mul word [bx+si+4]

; /5 IMUL
imul bl
imul bx
imul byte [bx+si+4]
imul word [bx+si+4]

; /6 DIV
div bl
div bx
div byte [bx+si+4]
div word [bx+si+4]

; /7 IDIV
idiv bl
idiv bx
idiv byte [bx+si+4]
idiv word [bx+si+4]

hlt
