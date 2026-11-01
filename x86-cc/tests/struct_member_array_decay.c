struct S { char a[8]; }; int sum(char *p) { return p[0]+p[1]; } int main(void) { struct S s; struct S *p; p=&s; p->a[0]=20; p->a[1]=22; return sum(p->a); }
