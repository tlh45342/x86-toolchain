struct S { int a[4]; };
int main(void)
{
    struct S s;
    struct S *p;
    int i;
    p = &s;
    i = 1;
    p->a[i] = 20;
    p->a[i + 1] = 22;
    return p->a[i] + p->a[i + 1];
}
