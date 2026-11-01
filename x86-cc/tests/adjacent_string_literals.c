int main(void)
{
    char *s;
    s = "abc" "def";
    if (s[0] != 'a') return 1;
    if (s[3] != 'd') return 2;
    if (s[5] != 'f') return 3;
    if (s[6] != 0) return 4;
    return 42;
}
