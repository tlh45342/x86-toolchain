/* Regression: keywords in literals must not allocate stack locals. */
extern int puts(const char *s);
int main(void)
{
    int value;
    value = 42;
    puts("short int long char unsigned signed const volatile");
    puts("escaped quote: \"short\" and backslash \\ char");
    return value;
}
