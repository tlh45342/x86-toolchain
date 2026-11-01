#define B 1
#define A B
#if A
int yes_a;
#else
int no_a;
#endif
#if defined A
int yes_defined_a;
#endif
#if defined(B)
int yes_defined_b;
#endif
#undef A
#ifndef A
int yes_undef;
#endif
