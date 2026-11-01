int copy_value(int *dst, int *src) {
    *dst = *src;
    return *dst;
}

int main(void) {
    int a = 0;
    int b = 42;
    return copy_value(&a, &b);
}
