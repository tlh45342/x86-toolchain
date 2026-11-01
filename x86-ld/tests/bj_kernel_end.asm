cpu 8086
bits 16
global _start
extern __kernel_end
_start:
    call __kernel_end
