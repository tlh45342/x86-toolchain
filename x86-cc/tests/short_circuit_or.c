int main(void) {
    int zero = 0;
    if (1 || (42 / zero)) return 42;
    return 0;
}
