/* Blackjack original 32-bit arithmetic runtime checks. */
int main(void)
{
    unsigned int narrow = 65535u;
    unsigned long wide = 1UL;
    unsigned long result;
    result = narrow + wide;
    if (result != 65536UL) return 11;
    result = wide + narrow;
    if (result != 65536UL) return 12;
    result = 0xFFFFFFFFUL + 1UL;
    if (result != 0UL) return 13;
    result = 0UL - 1UL;
    if (result != 0xFFFFFFFFUL) return 14;
    result = 0xFFFFFFFFUL * 2UL;
    if (result != 0xFFFFFFFEUL) return 15;
    return 42;
}
