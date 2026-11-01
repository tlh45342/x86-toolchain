#define HAVE_THING 1
#if defined(HAVE_THING)
#define ANSWER 42
#else
#define ANSWER 1
#endif
int main() { return ANSWER; }
