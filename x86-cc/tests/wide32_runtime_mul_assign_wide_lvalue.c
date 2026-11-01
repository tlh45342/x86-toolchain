/* Regression: 32-bit computed lvalue multiply assignment. */
int main(void) {
 unsigned long a[2];
 unsigned long *p;
 a[0] = 0x12345678UL;
 a[1] = 0xFFFFFFFFUL;
 a[0] *= 0x01000193UL;
 if (a[0] != 0x20641EE8UL) return 11;
 p = &a[1];
 *p *= 2UL;
 if (a[1] != 0xFFFFFFFEUL) return 12;
 *p *= 0UL;
 if (a[1] != 0UL) return 13;
 return 42;
}
