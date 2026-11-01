/* Regression: 32-bit global array storage and compound arithmetic. */
unsigned long g[2];
int main(void) {
 g[0] = 0x12345678UL;
 g[1] = 0xFFFFFFFFUL;
 if (g[0] != 0x12345678UL) return 11;
 g[0] *= 0x01000193UL;
 if (g[0] != 0x20641EE8UL) return 12;
 if (g[1] != 0xFFFFFFFFUL) return 13;
 return 42;
}
