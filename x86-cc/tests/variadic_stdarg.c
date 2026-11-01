int sum3(int tag, ...)
{
    char *ap;
    int a;
    int b;
    int c;
    __builtin_va_start(ap, tag);
    a = __builtin_va_arg(ap, int);
    b = __builtin_va_arg(ap, int);
    c = __builtin_va_arg(ap, int);
    return a + b + c;
}

int first_char(int tag, ...)
{
    char *ap;
    char *p;
    __builtin_va_start(ap, tag);
    p = __builtin_va_arg(ap, char *);
    return *p;
}

int main(void)
{
    if (sum3(0, 10, 12, 20) != 42) return 1;
    return first_char(0, "*");
}
