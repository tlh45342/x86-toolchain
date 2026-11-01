/* Regression for the C shell's nested arrays and pointer operations. */
#define STAGES 3
#define ARGS 4
#define TOKENS 16

int main(void)
{
    char *stages[STAGES][ARGS];
    char *tokens[TOKENS / 2];
    char word[8];
    char *end = word;
    char *missing = 0, *other = 0;
    int counts[STAGES];
    int row = 1;

    counts[0] = 0;
    counts[1] = 0;
    counts[2] = 0;
    tokens[0] = word;
    stages[row][counts[row]++] = tokens[0];
    if (counts[row] != 1)
        return 1;
    if (stages[row][0] != word)
        return 2;
    if (stages[row][0] != tokens[0])
        return 3;
    if (missing != other)
        return 4;
    ++end;
    if (end != word + 1)
        return 5;
    return 42;
}
