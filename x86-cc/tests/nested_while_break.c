int main(void) { int outer = 0; int n = 0; while (outer < 6) { int inner = 0; while (inner < 20) { n = n + 1; break; } outer = outer + 1; } return n + 36; }
