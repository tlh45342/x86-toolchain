/* Original Blackjack runtime test: 32-bit XOR. */
int main(void)
{
    unsigned long value;
    value = 0x811C9DC5UL ^ 0x72UL;
    if (value != 0x811C9DB7UL)
        return 11;
    return 42;
}
