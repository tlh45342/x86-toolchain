cpu 8086
bits 16
org 0x1000
    les bx,[bp+0x5A]
    cmpsb
    cmpsw
    repe cmpsb
    repz cmpsw
    stosw
    lodsw
