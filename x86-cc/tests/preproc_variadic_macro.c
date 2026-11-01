#define FIRST_PLUS(a,...) ((a)+(__VA_ARGS__))
int main(void)
{
    return FIRST_PLUS(20, 22);
}
