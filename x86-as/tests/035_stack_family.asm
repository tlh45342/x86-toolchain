bits 16

; Phase 39: original 8086 stack-family closure.
; GPR compact PUSH/POP encodings.
push ax
push cx
push dx
push bx
push sp
push bp
push si
push di
pop ax
pop cx
pop dx
pop bx
pop sp
pop bp
pop si
pop di

; Segment-register stack forms.  POP CS does not exist on 8086.
push es
push cs
push ss
push ds
pop es
pop ss
pop ds

; Flags stack forms.
pushf
popf

; r/m16 memory forms, including direct, base/index + disp8,
; BP-based addressing, and a segment override.
push word [0x2000]
pop word [0x2002]
push word [bx+si+4]
pop word [bx+si+6]
push word [bp+di+8]
pop word [bp+di+10]
push word [es:bx+si+12]
pop word [es:bx+si+14]

hlt
