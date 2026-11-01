/* C89 declaration-specifier order, derived from LACC typedef.c. */
const unsigned int typedef count_t;
typedef unsigned int other_t;
int main(void) {
    count_t n;
    other_t m;
    n = 40;
    m = 2;
    return n + m;
}
