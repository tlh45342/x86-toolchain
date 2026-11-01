int climb_ptr(int *p, int n) {
    if (n == 0) return *p;
    *p = *p + 1;
    return climb_ptr(p, n - 1);
}

int main(void) {
    int x = 39;
    return climb_ptr(&x, 3);
}
