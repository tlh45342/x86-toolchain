int main(void)
{
    int a[4];
    int *p = a;
    int i = 3;
    p[i] = 42;
    return p[i];
}
