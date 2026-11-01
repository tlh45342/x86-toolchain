/* Blackjack bj1 hash runtime regression. */
#include <stdint.h>
static uint32_t hash_pw(const char*u,const char*p)
{
    uint32_t h=2166136261u,i=0;
    while(u[i]) { h^=(uint8_t)u[i++]; h*=16777619u; }
    h^=0x3au; h*=16777619u; i=0;
    while(p[i]) { h^=(uint8_t)p[i++]; h*=16777619u; }
    return h;
}
int main(void)
{
    if (hash_pw("root", "toor") != 0x769090e1UL) return 11;
    if (hash_pw("root", "wrong") == 0x769090e1UL) return 12;
    return 42;
}
