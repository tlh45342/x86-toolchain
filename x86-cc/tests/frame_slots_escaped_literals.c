/* Regression: frame prepass must skip escaped quotes/backslashes. */
extern int puts(const char *s);
int main(void)
{
    int result;
    char quote;
    char slash;
    result = 42;
    quote = '\'';
    slash = '\\';
    puts("short \\\"int\\\" long");
    puts("short \\\\\\\" int");
    puts("short \\\\\\\\ int");
    puts("char 'unsigned' signed volatile");
    if (quote != 39 || slash != 92)
        return 1;
    return result;
}
