int main(void)
{
    asm {
        cli
        xor ax, ax
        mov ds, ax
        mov es, ax
        sti
    }
    return 42;
}
