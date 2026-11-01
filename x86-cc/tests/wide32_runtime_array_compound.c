/* Regression: wide array compound arithmetic and adjacent elements. */
int main(void) {
 unsigned long a[3];
 unsigned long *p;
 a[0] = 0xFFFFFFFFUL;
 a[1] = 0x12345678UL;
 a[2] = 0x80000000UL;
 a[0] += 1UL;
 if (a[0] != 0UL) return 11;
 a[1] -= 0x12340000UL;
 if (a[1] != 0x5678UL) return 12;
 a[2] ^= 0xFFFFFFFFUL;
 if (a[2] != 0x7FFFFFFFUL) return 13;
 p = &a[1];
 *p += 0x10000UL;
 if (a[1] != 0x15678UL) return 14;
 *p -= 0x20000UL;
 if (a[1] != 0xFFFF5678UL) return 15;
 *p ^= 0xFFFF0000UL;
 if (a[1] != 0x5678UL) return 16;
 if (a[0] != 0UL) return 17;
 if (a[2] != 0x7FFFFFFFUL) return 18;
 return 42;
}
