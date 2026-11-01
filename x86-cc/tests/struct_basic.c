struct Pair {
    int a;
    int b;
};

int main(void) {
    struct Pair p;
    p.a = 10;
    p.b = 32;
    return p.a + p.b;
}
