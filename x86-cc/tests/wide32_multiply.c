/* Verify unsigned 32-bit multiplication with wraparound. */
unsigned long multiply(unsigned long value)
{
    return value * 16777619UL;
}
