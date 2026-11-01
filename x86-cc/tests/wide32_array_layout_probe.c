int main(void) {
 unsigned long a[2];
 a[0] = 0x12345678UL;
 a[1] = 0xFFFFFFFFUL;
 if (a[0] != 0x12345678UL) return 11;
 if (a[1] != 0xFFFFFFFFUL) return 12;
 return 42;
}
