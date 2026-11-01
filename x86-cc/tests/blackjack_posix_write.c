#include <unistd.h>
int main(void) { return write(1, "OK\n", 3) == 3 ? 42 : 1; }
