struct Pair { int a; int b; };
int main(void) { struct Pair x; struct Pair *p = &x; p->a = 20; p->b = 22; return p->a + p->b; }
