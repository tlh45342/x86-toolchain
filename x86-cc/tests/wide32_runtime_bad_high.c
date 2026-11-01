/* Blackjack regression: equality must compare the upper word. */
int main(void)
{
    unsigned long value;
    value = 0x12345678UL * 0x01000193UL;
    if (value == 0x99991EE8UL)
        return 11;
    return 42;
}
