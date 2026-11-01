#include "local_types.h"
extern int add(word_t a, word_t b);
int add(word_t a, word_t b) { return a + b; }
int main(void) { return add(40, 2); }
