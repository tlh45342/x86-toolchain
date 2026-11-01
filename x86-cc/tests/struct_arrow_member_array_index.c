struct S { char a[8]; int n; };
int main(void)
{
    struct S s;
    struct S *p;
    int i;
    p = &s;
    i = 3;
    p->a[i - 1] = 40;
    p->a[i] = 2;
    return p->a[i - 1] + p->a[i];
}
