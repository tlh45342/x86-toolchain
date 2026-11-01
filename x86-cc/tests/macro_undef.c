#define VALUE 7
#undef VALUE
#ifndef VALUE
#define VALUE 42
#endif

int main(void)
{
    return VALUE;
}
