int main(void) { int outer = 0; int n = 0; while (outer < 6) { outer = outer + 1; int inner = 0; while (inner < 8) { inner = inner + 1; if (inner < 8) continue; n = n + 1; } } return n + 36; }
