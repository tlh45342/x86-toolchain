struct B { char a[1200]; int n; }; int main(void) { struct B b; struct B *p; p=&b; p->a[1199]=42; return p->a[1199]; }
