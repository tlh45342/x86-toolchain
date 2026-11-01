struct S { int x; int y; int z; };
int main(void)
{
 struct S a;
 struct S *p=&a;
 p->x=42;
 if(p+1==p+1) return p->x;
 return 0;
}
