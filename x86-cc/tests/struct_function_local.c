struct Pair {
    int a;
    int b;
};

int build(void) {
    struct Pair p;
    p.a = 21;
    p.b = 21;
    return p.a + p.b;
}

int main(void) {
    return build();
}
