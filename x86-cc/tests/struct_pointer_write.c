struct Pair { int a; int b; };
int main(void) { struct Pair p; struct Pair *q = &p; q->a = 10; q->b = 32; return p.a + p.b; }
