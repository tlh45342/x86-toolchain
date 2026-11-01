#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../peephole.h"
int main(int argc, char **argv) {
    if (argc != 3) return 2;
    return peephole_optimize_file(argv[1], atoi(argv[2])) ? 0 : 1;
}
