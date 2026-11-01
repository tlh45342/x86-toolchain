#include <unistd.h>
struct E { char screen[512]; };
struct E g;
static int append_char(char *b,int p,int cap,int c){if(p<cap){b[p]=c;p=p+1;}return p;}
int f(struct E *e) { int p; p=0; p=append_char(e->screen,p,510,27); p=append_char(e->screen,p,510,'['); return write(1,e->screen,p); }
int main(void) { return 42; }
