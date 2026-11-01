struct pair {
    int a, b;
} const pairs[] = { { 20, 22 } };
int main(void)
{
    struct pair x;
    x.a = 42;
    return x.a;
}
