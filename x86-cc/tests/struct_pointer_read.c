struct Pair { int a; int b; };
int main(void) { struct Pair p; struct Pair *q = &p; p.a = 10; p.b = 32; return q->a + q->b; }
