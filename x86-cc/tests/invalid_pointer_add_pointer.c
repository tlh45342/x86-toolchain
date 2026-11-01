int main(void) {
    int a[2];
    int *p = a;
    int *q = a;
    p = p + q;
    return 0;
}
