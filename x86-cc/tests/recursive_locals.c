int sum_local(int n) {
    int here = n;
    if (n == 0) return 0;
    return here + sum_local(n - 1);
}

int main(void) {
    return sum_local(6) + 21;
}
