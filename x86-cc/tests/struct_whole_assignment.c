struct Pair { int a; int b; };
int main(void)
{
 struct Pair a;
 struct Pair b;
 b.a=40;
 b.b=2;
 a=b;
 if(a.a!=40) return 1;
 if(a.b!=2) return 2;
 return 42;
}
