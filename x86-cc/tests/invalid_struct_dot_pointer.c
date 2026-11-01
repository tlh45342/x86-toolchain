struct Pair { int a; int b; };
int main(void) { struct Pair p; struct Pair *q = &p; return q.a; }
