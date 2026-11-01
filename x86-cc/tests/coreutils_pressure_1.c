/* Language pressure distilled from GNU coreutils echo/basename/dirname.
 * No libc dependency: this tests C, not the target runtime. */
int classify(char c)
{
    switch (c) {
    case 'a': case 'A': return 10;
    case 'b': case 'B': return 11;
    default: return c - '0';
    }
}

int main(void)
{
    char text[4];
    char *p;
    int n = 0;
    text[0] = '1';
    text[1] = 'a';
    text[2] = '2';
    text[3] = 0;
    p = text;
    while (*p) {
        n += classify(*p++);
    }
    return n;
}
