cpu 8086
bits 16
org 0x1000

; Phase 35: close the complete 8086 Group-1 immediate family.
; For every /digit family member, exercise:
;   80 /n ib       byte register
;   83 /n ib       word register, sign-extended imm8
;   81 /n iw       word register, imm16
;   80 /n ib       byte memory
;   83 /n ib       word memory, sign-extended imm8
;   81 /n iw       word memory, imm16

add bl, 0x12
add bx, 0x12
add bx, 0x1234
add byte [bx+si], 0x12
add word [bx+si], 0x12
add word [bx+si], 0x1234

or bl, 0x12
or bx, 0x12
or bx, 0x1234
or byte [bx+si], 0x12
or word [bx+si], 0x12
or word [bx+si], 0x1234

adc bl, 0x12
adc bx, 0x12
adc bx, 0x1234
adc byte [bx+si], 0x12
adc word [bx+si], 0x12
adc word [bx+si], 0x1234

sbb bl, 0x12
sbb bx, 0x12
sbb bx, 0x1234
sbb byte [bx+si], 0x12
sbb word [bx+si], 0x12
sbb word [bx+si], 0x1234

and bl, 0x12
and bx, 0x12
and bx, 0x1234
and byte [bx+si], 0x12
and word [bx+si], 0x12
and word [bx+si], 0x1234

sub bl, 0x12
sub bx, 0x12
sub bx, 0x1234
sub byte [bx+si], 0x12
sub word [bx+si], 0x12
sub word [bx+si], 0x1234

xor bl, 0x12
xor bx, 0x12
xor bx, 0x1234
xor byte [bx+si], 0x12
xor word [bx+si], 0x12
xor word [bx+si], 0x1234

cmp bl, 0x12
cmp bx, 0x12
cmp bx, 0x1234
cmp byte [bx+si], 0x12
cmp word [bx+si], 0x12
cmp word [bx+si], 0x1234

hlt
