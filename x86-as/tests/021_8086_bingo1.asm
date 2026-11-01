cpu 8086
bits 16
org 0x1000
    test al, 0x80
    test ax, 0x80B5
    test bx, cx
    test word [bp+4], ax
    std
    scasb
    scasw
    repe scasw
    sub byte [cs:si+0x12], 0x10
    ret
    ret 4
    retf
    retf 6
