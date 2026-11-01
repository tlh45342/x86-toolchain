#include <unistd.h>
struct E { char text[512]; char screen[512]; char *path; int len; int top; };
struct E g;
static int ac(char*b,int p,int cap,int c){if(p<cap){b[p]=c;p=p+1;}return p;}
int f(struct E *e){int p,i,rows,rc;p=0;rows=0;i=e->top;while(i<e->len && rows<23 && p<430){if(e->text[i]==10){p=ac(e->screen,p,500,13);p=ac(e->screen,p,500,10);rows=rows+1;}else p=ac(e->screen,p,500,e->text[i]);i=i+1;}rc=write(1,e->screen,p);return rc;}
int main(void){return 42;}
