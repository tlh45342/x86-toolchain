bits 64
section .text
global _start, message

_start:
    lea rsi, [rel message]
    syscall

message:
    db "X", 0
