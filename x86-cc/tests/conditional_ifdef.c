#define ENABLED 1
#ifdef ENABLED
int main(void) { return 42; }
#else
int main(void) { return 1; }
#endif
