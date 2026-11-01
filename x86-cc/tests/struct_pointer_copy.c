struct Pair { int a; int b; };
int main(void) { struct Pair x; struct Pair *p = &x; struct Pair *q = p; q->b = 42; return p->b; }
