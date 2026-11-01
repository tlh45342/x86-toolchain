int main(void)
{
    if (sizeof(char) != 1) return 1;
    if (sizeof(int) != 2) return 2;
    if (sizeof(char *) != 2) return 3;
    return 42;
}
