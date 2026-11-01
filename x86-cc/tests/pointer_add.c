int main(void) {
    int a[3];
    int *p = a;
    p = p + 1;
    *p = 42;
    return a[1];
}
