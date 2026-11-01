struct Pair {
    int a;
    int b;
};

int main(void) {
    struct Pair p;
    p.a = 40;
    p.b = p.a;
    p.b = p.b - 38;
    return p.a + p.b;
}
