cpu 8086
bits 16
org 0x1000
    mov ax, 0
    mov ds, ax
    mov es, ax

    mov bh, 1
    add bh, bh
    mov ax, 0x1000
    mov bx, 0x0010
    add ax, bx
    add bx, ax
    add al, 1
    add ax, 0x0010

    mov ax, 1
    mov bx, 2
    adc ax, bx
    adc bx, ax
    adc al, 1
    adc ax, 1

    mov ax, 10
    mov bx, 3
    sbb ax, bx
    sbb bx, ax
    sbb al, 1
    sbb ax, 1

    mov ax, 20
    mov bx, 3
    sub ax, bx
    sub bx, ax
    sub al, 1
    sub ax, 1

    cmp ax, bx
    cmp bx, ax
    cmp al, 1
    cmp ax, 1

    mov ah, 0x10
    add ah, 8
    mov cx, 1
    sbb cx, -2

    mov bl, 0x0F
    not bl
    mov dx, 0x00FF
    not dx
    mov ax, 1
    shl ax, 1

    mov cx, 0
    jcxz jcxz_ok
    mov si, 0xDEAD
jcxz_ok:
    mov si, 0xBEEF
    hlt
