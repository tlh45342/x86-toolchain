void helper(void);

__naked void entry(void)
{
    asm {
        cli
        xor ax, ax
        mov ss, ax
        mov sp, 0x7C00
        call helper
    .hang:
        hlt
        jmp .hang
    }
}

void helper(void)
{
}
