#include <unistd.h>
struct E { char text[512]; char screen[512]; char cmd[8]; char *path; int fd; int len; int cursor; int top; int mode; int dirty; int cmdn; int is_new; };
struct E g;
int f(struct E *e) { int p; p=7; return write(1,e->screen,p); }
int main(void) { return 42; }
