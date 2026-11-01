cpu 8086
bits 16
org 0x8000
start:
    db "GUPPY BOOT1", 13, 10, 0
    db 'A'
    db "A", 'B', 0x43, 0
    mov al, '0'
    add al, '0'
    cmp al, '9'
