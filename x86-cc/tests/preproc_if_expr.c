#define A 2
#define B 3
#if defined(A) && (A + B == 5)
int main(void) { return 42; }
#else
int main(void) { return 1; }
#endif
