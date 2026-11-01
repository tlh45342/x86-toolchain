bits 16
global _start
_start:
    push word [target]
    pop word [target]
    test word [target],0x1234
    xchg ax,[target]
    inc word [target]
    dec word [target]
    lea ax,[target]
    shl word [target],1
    shr word [target],cl
    not word [target]
    neg word [target]
    mul word [target]
    les ax,[target]
    lds bx,[target]
    add word [target],ax
    mov word [target],0x1234
    hlt
target: dw 0,0
