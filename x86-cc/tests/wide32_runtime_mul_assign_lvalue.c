/* Regression: multiplication assignment through computed lvalues. */
int main(void)
{
    unsigned int a[2];
    unsigned int *p;
    a[0] = 7;
    a[1] = 9;
    a[0] *= 6;
    if (a[0] != 42) return 11;
    p = &a[1];
    *p *= 5;
    if (a[1] != 45) return 12;
    return 42;
}
