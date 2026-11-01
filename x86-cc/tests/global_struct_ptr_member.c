struct S { int (*fn)(int); };
static struct S gs;
static int f(int x){ return x; }
int main(void){ gs.fn=f; return 42; }
