struct Pair { int a; int b; };
int main(void) { struct Pair a; struct Pair b; struct Pair *p = &a; a.b = 1; b.b = 42; p = &b; return p->b; }
