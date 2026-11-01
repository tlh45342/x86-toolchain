#define CAT(x,y) x ## y
#define XCAT(x,y) CAT(x,y)
#define FOO foo
#define BAR bar
int main(void)
{
    int foo, bar, foobar;
    foo = 20;
    bar = 22;
    CAT(foo,bar) = foo + bar;
    XCAT(FOO,BAR) = foo + bar;
    return foobar;
}
