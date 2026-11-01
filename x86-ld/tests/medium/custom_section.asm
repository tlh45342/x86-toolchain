; Acceptance fixture for section-aware Medium model.
; EXPECTED FUTURE RESULT: linked execution exits with AX=0x002A.
; Current assembler intentionally rejects .drivers until named-section
; emission and linker placement are implemented.

bits 16
section .text
global _start
extern driver_entry
_start:
    call far driver_entry
    hlt

section .drivers
global driver_entry
driver_entry:
    mov ax, 42
    retf
