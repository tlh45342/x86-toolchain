#define A 42
#define ID(x) x
#define WRAP(x) ID(x)
int main(void) { return WRAP(A); }
