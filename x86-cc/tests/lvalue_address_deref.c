int main(void) {
    int x = 42;
    int *p = &x;
    int *q = &*p;
    return *q;
}
