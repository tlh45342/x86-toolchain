int sum_to(int n);

int main(void)
{
    return sum_to(6) + 21;
}

int sum_to(int n)
{
    if (n == 0)
        return 0;
    return n + sum_to(n - 1);
}
