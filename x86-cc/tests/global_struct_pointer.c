struct Pair { int a; char b; int c; };
struct Pair g;
int main(void) { struct Pair *p=&g; p->a=20; p->b=2; p->c=20; return p->a+p->b+p->c; }
