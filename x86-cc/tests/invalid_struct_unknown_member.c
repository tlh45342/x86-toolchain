struct Pair { int a; int b; };
int main(void) {
    struct Pair p;
    p.c = 42;
    return p.a;
}
