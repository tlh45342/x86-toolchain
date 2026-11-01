int peek(const void *p);
int peek(const void *p) {
    return 42;
}
int main(void) {
    int x;
    return peek(&x);
}
