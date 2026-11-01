/* Original Blackjack 32-bit AND/OR regression. */
int main(void)
{
    unsigned long value;
    value = 0xF0F01234UL & 0x0FF0FFFFUL;
    if (value != 0x00F01234UL)
        return 11;
    value = 0x10000001UL | 0x02004000UL;
    if (value != 0x12004001UL)
        return 12;
    return 42;
}
