int first(int *p)
{
    return *p;
}

int main(void)
{
    int a[2];
    a[0] = 42;
    a[1] = 7;
    return first(a);
}
