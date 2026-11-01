#include <stdint.h>
extern int take(const uint16_t *p, uint16_t n);
int take(const uint16_t *p, uint16_t n) {
    return p[0] + n;
}
int main(void) {
    int a[1];
    a[0] = 40;
    return take(a, 2);
}
