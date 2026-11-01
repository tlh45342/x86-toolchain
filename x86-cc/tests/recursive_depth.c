int climb(int n) {
    if (n == 0) return 0;
    return 2 + climb(n - 1);
}

int main(void) {
    return climb(21);
}
