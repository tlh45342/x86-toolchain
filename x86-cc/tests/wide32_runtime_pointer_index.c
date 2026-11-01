/* Regression: 32-bit pointer indexing and stride. */
int main(void) {
 unsigned long a[3];
 unsigned long *p;
 a[0] = 0x11112222UL;
 a[1] = 0x33334444UL;
 a[2] = 0x55556666UL;
 p = &a[0];
 if (p[1] != 0x33334444UL) return 11;
 p[1] = 0xABCDEF01UL;
 if (a[1] != 0xABCDEF01UL) return 12;
 p[2] += 0x10000UL;
 if (a[2] != 0x55566666UL) return 13;
 if (a[0] != 0x11112222UL) return 14;
 return 42;
}
