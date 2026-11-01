int main(void)
{
    int a[3];
    int *p = a;
    a[1] = 42;
    if (p[1] == *(p + 1))
        return p[1];
    return 0;
}
