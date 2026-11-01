struct S { char a[8]; }; int main(void) { struct S s; int i; i=2; s.a[i]=40; s.a[i+1]=2; return s.a[i]+s.a[i+1]; }
