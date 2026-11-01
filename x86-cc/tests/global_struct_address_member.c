struct A { int x; };
struct B { struct A *p; };
static struct A a;
static struct B b;
int main(void){ b.p=&a; return 42; }
