#define CAT(x,y) x ## y
#define XCAT(x,y) CAT(x,y)
#define FOO foo
#define BAR bar
int main(void)
{
    int foobar = 42;
    return XCAT(FOO,BAR);
}
