int main(void) {
 unsigned a;
 a = 0xffff;
 a += 1;
 if (a != 0) return 11;
 a -= 1;
 if (a != 0xffff) return 12;
 a ^= 0x8000;
 if (a != 0x7fff) return 13;
 a *= 2;
 if (a != 0xfffe) return 14;
 a &= 0x0fff;
 if (a != 0xffe) return 15;
 a |= 0xf000;
 if (a != 0xfffe) return 16;
 return 42;
}
