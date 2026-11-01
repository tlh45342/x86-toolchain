int main(void) {
    int a[4];
    int i = 2;
    int *p = a + i;
    *p = 42;
    return a[2];
}
