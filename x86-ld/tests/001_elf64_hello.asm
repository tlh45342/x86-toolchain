bits 64
section .text
global _start, message

_start:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel message]
    mov rdx, 18
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall

message:
    db "HELLO FROM X86-LD", 10
