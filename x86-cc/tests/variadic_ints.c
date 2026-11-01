int sum3(int tag, ...)
{
    char *ap;
    int a;
    int b;
    int c;
    __builtin_va_start(ap, tag);
    a = __builtin_va_arg_int(ap);
    b = __builtin_va_arg_int(ap);
    c = __builtin_va_arg_int(ap);
    return a + b + c;
}

int main(void)
{
    return sum3(0, 10, 12, 20);
}
