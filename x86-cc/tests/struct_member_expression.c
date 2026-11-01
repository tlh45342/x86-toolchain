struct Pair {
    int left;
    int right;
};

int main(void) {
    struct Pair p;
    int n = 2;
    p.left = 20;
    p.right = 1;
    p.right = p.right + n;
    return p.left * n + p.right - 1;
}
