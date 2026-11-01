/* Blackjack regression: 16-bit unsigned plus 32-bit unsigned. */
int main(void)
{
    unsigned int low_word = 0xFFFFu;
    unsigned long high_word = 1UL;
    unsigned long combined;

    combined = low_word + high_word;
    if (combined != 65536UL) {
        return 1;
    }

    return 0;
}
