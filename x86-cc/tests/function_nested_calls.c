int add(int a, int b)
{
    return a + b;
}

int main(void)
{
    return add(add(10, 10), add(11, 11));
}
