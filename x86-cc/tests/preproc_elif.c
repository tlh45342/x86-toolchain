#define ZERO 0
#define ONE 1
#if ZERO
int wrong0;
#elif ONE
int yes1;
#else
int wrong1;
#endif
#if ONE
int yes2;
#elif ONE
int wrong2;
#else
int wrong3;
#endif
