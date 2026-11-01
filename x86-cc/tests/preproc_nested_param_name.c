#define INNER_N(N) case 'a' + (N): case 'b' + (N)
#define OUTER_N(N) INNER_N(N): case 'z' + (N)
OUTER_N(0)
OUTER_N('A' - 'a')
