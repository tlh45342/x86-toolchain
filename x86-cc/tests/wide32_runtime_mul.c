/* Blackjack original runtime regression for 32-bit multiplication. */
int main(void)
{
    unsigned long value;
    value = 0x12345678UL * 0x01000193UL;
    if (value != 0x20641EE8UL)
        return 11;
    return 42;
}
