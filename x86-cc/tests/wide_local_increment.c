#include <stdint.h>
int helper(void) { return 0; }
int main(void) {
    uint32_t n = 41;
    ++n;
    return n + helper();
}
