bits 16
org 0x1000

; Phase 36: primary arithmetic/logical register <-> r/m rows.
; For each Group-1 family member, close all four opcode rows:
;   base+0 r/m8,r8   base+1 r/m16,r16
;   base+2 r8,r/m8   base+3 r16,r/m16

add bl, cl
add bx, cx
add byte [bx+si+4], cl
add word [bx+si+4], cx
add cl, byte [bx+si+4]
add cx, word [bx+si+4]

or bl, cl
or bx, cx
or byte [bx+si+4], cl
or word [bx+si+4], cx
or cl, byte [bx+si+4]
or cx, word [bx+si+4]

adc bl, cl
adc bx, cx
adc byte [bx+si+4], cl
adc word [bx+si+4], cx
adc cl, byte [bx+si+4]
adc cx, word [bx+si+4]

sbb bl, cl
sbb bx, cx
sbb byte [bx+si+4], cl
sbb word [bx+si+4], cx
sbb cl, byte [bx+si+4]
sbb cx, word [bx+si+4]

and bl, cl
and bx, cx
and byte [bx+si+4], cl
and word [bx+si+4], cx
and cl, byte [bx+si+4]
and cx, word [bx+si+4]

sub bl, cl
sub bx, cx
sub byte [bx+si+4], cl
sub word [bx+si+4], cx
sub cl, byte [bx+si+4]
sub cx, word [bx+si+4]

xor bl, cl
xor bx, cx
xor byte [bx+si+4], cl
xor word [bx+si+4], cx
xor cl, byte [bx+si+4]
xor cx, word [bx+si+4]

cmp bl, cl
cmp bx, cx
cmp byte [bx+si+4], cl
cmp word [bx+si+4], cx
cmp cl, byte [bx+si+4]
cmp cx, word [bx+si+4]

hlt
