/* Regression: suffixed zero and one retain 32-bit expression width. */
int main(void)
{
    unsigned long a;
    a = 0UL - 1UL;
    if (a != 0xFFFFFFFFUL) return 11;
    return 42;
}
