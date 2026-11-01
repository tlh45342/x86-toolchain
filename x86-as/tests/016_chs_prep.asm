cpu 8086
bits 16
org 0x1000
    test dl,dl
    mul byte [bp+0x1A]
    xchg ax,cx
    div cx
    xchg ax,dx
    div byte [bp+0x18]
    ror cl,1
    or cl,ah
    inc cx
    jc short done
done:
    hlt
