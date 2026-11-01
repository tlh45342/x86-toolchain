cpu 8086
bits 16
org 0x1000
    cmp al, 'x'
    jnz short nope
    nop
nope:
    call subr
    hlt
subr:
    ret
