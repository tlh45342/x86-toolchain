int main(void) {
 unsigned long a;
 a = 0x12345678UL;
 a <<= 4;
 if (a != 0x23456780UL) return 11;
 a >>= 8;
 if (a != 0x00234567UL) return 12;
 return 42;
}
