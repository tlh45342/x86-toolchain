int main(void) {
    int x = 10;
    int y = 32;
    int *p = &x;
    int *q = &y;
    *p = *p + *q;
    return x;
}
