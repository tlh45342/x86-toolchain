int main(void) {
 unsigned long a[2];
 a[0] = 0x12345678UL;
 if (a[0] != 0x12345678UL) return 11;
 return 42;
}
