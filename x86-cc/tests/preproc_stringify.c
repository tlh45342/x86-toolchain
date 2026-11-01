#define STR_RAW(x) #x
#define STR(x) STR_RAW(x)
#define VALUE hello
int main(void)
{
    char *s = STR(VALUE);
    return 42;
}
