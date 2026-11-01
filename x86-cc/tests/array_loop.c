int main(void)
{
    int a[3];
    int i = 0;
    while (i < 3) {
        a[i] = i + 12;
        i = i + 1;
    }
    return a[0] + a[1] + a[2] + 3;
}
