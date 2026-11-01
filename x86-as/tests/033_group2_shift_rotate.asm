cpu 8086
bits 16
org 0x1000

; Phase 37: original 8086 Group-2 rotate/shift closure.
; Each operation covers byte/word and count 1/CL, using both registers
; and memory so D0/D1/D2/D3 and the complete defined /digit map are fenced.

rol al, 1
rol ax, 1
rol byte [bx+si+4], cl
rol word [bx+si+4], cl

ror cl, 1
ror cx, 1
ror byte [bx+si+4], cl
ror word [bx+si+4], cl

rcl dl, 1
rcl dx, 1
rcl byte [bx+si+4], cl
rcl word [bx+si+4], cl

rcr bl, 1
rcr bx, 1
rcr byte [bx+si+4], cl
rcr word [bx+si+4], cl

shl ah, 1
shl sp, 1
shl byte [bx+si+4], cl
shl word [bx+si+4], cl

shr ch, 1
shr bp, 1
shr byte [bx+si+4], cl
shr word [bx+si+4], cl

sar dh, 1
sar si, 1
sar byte [bx+si+4], cl
sar word [bx+si+4], cl

; SAL is the architectural synonym for SHL and must encode identically.
sal al, 1
sal ax, cl
