int main(void) {
    int a[3];
    int *p = a + 2;
    p = p - 1;
    *p = 42;
    return a[1];
}
