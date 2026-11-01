int main(void) {
 unsigned long a[2];
 unsigned long *p;
 a[0] = 0xF0F00F0FUL;
 a[1] = 0x12345678UL;
 a[0] &= 0x0FF0FF00UL;
 if (a[0] != 0x00F00F00UL) return 11;
 p = &a[1];
 *p |= 0x80000001UL;
 if (a[1] != 0x92345679UL) return 12;
 if (a[0] != 0x00F00F00UL) return 13;
 return 42;
}
