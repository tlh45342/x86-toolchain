int main(void)
{
    int x;
    x = 3;
    while (x)
        x = x - 1;
    ;
    for (x = 2; x; x = x - 1)
        ;
    if (x)
        return 1;
    return 0;
}
