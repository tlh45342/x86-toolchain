struct S { int a; int b; };
static struct S gs;
struct S *get(void){ return &gs; }
int main(void){ return 42; }
