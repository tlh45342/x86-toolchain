int put(int *p, int i)
{
    p[i] = 42;
    return p[i];
}

int main(void)
{
    int a[3];
    return put(a, 2);
}
