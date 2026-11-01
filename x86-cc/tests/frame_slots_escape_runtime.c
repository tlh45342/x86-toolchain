/* Runtime check of decoded escapes and frame scanner agreement. */
int main(void)
{
    const char *a;
    const char *b;
    const char *c;
    int result;
    a = "short \"int\"";
    b = "long \\ char";
    c = "signed\nunsigned\tconst";
    result = 42;
    if (a[6] != 34 || a[10] != 34 || a[11] != 0)
        return 1;
    if (b[5] != 92 || b[6] != 32)
        return 2;
    if (c[6] != 10 || c[15] != 9)
        return 3;
    if ('\'' != 39 || '\\' != 92)
        return 4;
    return result;
}
