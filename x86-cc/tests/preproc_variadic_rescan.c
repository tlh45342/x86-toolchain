#define A 42
#define ID(X) X
#define CALL(F,...) F(__VA_ARGS__)
int main(void)
{
    return CALL(ID,A);
}
