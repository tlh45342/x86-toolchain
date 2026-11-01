/* FNV-1a core for Blackjack's educational bj1 password format. */
unsigned long hash_byte(unsigned long value, unsigned char character)
{
    value = value ^ character;
    value = value * 16777619UL;
    return value;
}
