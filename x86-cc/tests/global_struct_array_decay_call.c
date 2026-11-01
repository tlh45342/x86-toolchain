#include <unistd.h>
struct E { char screen[512]; int n; };
struct E g;
int f(struct E *e) { int p; p=7; return write(1,e->screen,p); }
int main(void) { return 42; }
