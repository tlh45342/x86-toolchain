int set42(int *p) {
    *p = 42;
    return 0;
}

int main(void) {
    int x = 0;
    int ignored = set42(&x);
    return x;
}
