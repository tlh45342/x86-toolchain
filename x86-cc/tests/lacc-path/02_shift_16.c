int main(void) {
 unsigned a;
 a = 3;
 a <<= 4;
 if (a != 48) return 11;
 a >>= 2;
 if (a != 12) return 12;
 return 42;
}
