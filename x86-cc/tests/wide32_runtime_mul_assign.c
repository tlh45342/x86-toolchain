/* Regression: *= widths, wraparound, and mixed-width operands. */
int main(void)
{
    unsigned int small = 300;
    unsigned long wide = 0x12345678UL;
    unsigned long zero = 0UL;
    unsigned long one = 1UL;
    wide *= 0x01000193UL;
    if (wide != 0x20641EE8UL) return 11;
    wide *= 0UL;
    if (wide != 0UL) return 12;
    zero *= 0xFFFFFFFFUL;
    if (zero != 0UL) return 13;
    one *= 0xFFFFFFFFUL;
    if (one != 0xFFFFFFFFUL) return 14;
    wide = 0xFFFFFFFFUL;
    wide *= 2;
    if (wide != 0xFFFFFFFEUL) return 15;
    small *= 3;
    if (small != 900) return 16;
    small *= 0;
    if (small != 0) return 17;
    return 42;
}
