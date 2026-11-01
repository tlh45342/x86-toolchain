cpu 8086
bits 16
global _start
extern answer
_start:
    call answer
    hlt
