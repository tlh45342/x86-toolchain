struct S { int a; int b; };
static struct S gs;
int main(void)
{
 gs.a=42;
 return 42;
}
