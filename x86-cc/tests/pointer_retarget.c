int main(void)
{
    int x = 1;
    int y = 42;
    int *p = &x;
    p = &y;
    return *p;
}
