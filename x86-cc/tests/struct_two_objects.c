struct Pair {
    int a;
    int b;
};

int main(void) {
    struct Pair x;
    struct Pair y;
    x.a = 11;
    x.b = 9;
    y.a = 13;
    y.b = 9;
    return x.a + x.b + y.a + y.b;
}
