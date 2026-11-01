#define A 42
#define ID(X) X
#define WRAP(X) ID(X)
int main(void)
{
    return WRAP(A);
}
