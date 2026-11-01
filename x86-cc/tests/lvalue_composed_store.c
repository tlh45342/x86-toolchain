int main(void) {
    int x = 0;
    *(&x) = 42;
    return x;
}
