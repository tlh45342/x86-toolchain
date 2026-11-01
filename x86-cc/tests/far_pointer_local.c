/*
 * Regression: Blackjack16 function-local far pointers.
 *
 * A far pointer is a 32-bit segment:offset object.  Exercise both declaration
 * initialization and later assignment, then dereference through ES.
 */
unsigned char
far_local_initialized(void)
{
    unsigned char far *pointer = (unsigned char far *)0x00007DFEUL;

    return pointer[0];
}

unsigned char
far_local_assigned(void)
{
    unsigned char far *pointer;

    pointer = (unsigned char far *)0x00007DFFUL;

    return pointer[0];
}

int
main(void)
{
    return far_local_initialized() == 0x55
        && far_local_assigned() == 0xAA
        ? 0
        : 1;
}
