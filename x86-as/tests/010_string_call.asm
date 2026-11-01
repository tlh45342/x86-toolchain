cpu 8086
bits 16
org 0x1000
start:
    stosb
    lodsb
    call worker
    hlt
worker:
    ret
