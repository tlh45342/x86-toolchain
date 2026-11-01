/* Original Blackjack shift regression. */
int main(void)
{
    unsigned long value;
    value = 0x811C9DC5UL >> 4;
    if (value != 0x0811C9DCUL)
        return 11;
    value = 0x00012345UL << 4;
    if (value != 0x00123450UL)
        return 12;
    return 42;
}
