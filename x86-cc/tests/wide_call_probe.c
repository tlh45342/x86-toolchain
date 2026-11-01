#include <stdint.h>
extern int bj_write(int,const void*,uint32_t);
static uint32_t slen(const char*s){uint32_t n=0;while(s&&s[n])++n;return n;}
int main(void){int z;z=bj_write(1,"x",slen("x"));return 42;}
