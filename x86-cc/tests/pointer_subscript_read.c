int second(int *p)
{
    return p[1];
}

int main(void)
{
    int a[2];
    a[0] = 7;
    a[1] = 42;
    return second(a);
}
