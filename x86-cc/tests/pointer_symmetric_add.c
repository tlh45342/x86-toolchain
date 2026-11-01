int main(void) {
    int a[3];
    int *p = 1 + a;
    *p = 42;
    return a[1];
}
