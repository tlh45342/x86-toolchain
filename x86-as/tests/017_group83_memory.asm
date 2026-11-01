cpu 8086
bits 16
org 0x1000
    add word [bp-0x38], byte 1
    adc word [bp-0x36], byte 0
    sub word [bp-0x34], byte 1
    cmp word [bp-0x32], byte 7
    dec di
