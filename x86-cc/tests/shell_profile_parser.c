/* Regression: valid C prompt parsing constructs used by Blackjack shell. */
extern int strncmp(const char *, const char *, unsigned int);
int prompt_parse(const char *line)
{
    if (strncmp(line, "export ", 7) == 0)
        line += 7;
    if (strncmp(line, "PS1=", 4) == 0)
        return 1;
    return 0;
}
