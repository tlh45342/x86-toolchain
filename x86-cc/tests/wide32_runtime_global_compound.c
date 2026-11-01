/* LACC-inspired global scalar compound arithmetic and carry/borrow. */
unsigned long x;
int main(void) {
 x = 0xFFFFFFFFUL;
 x += 1UL;
 if (x != 0UL) return 11;
 x -= 1UL;
 if (x != 0xFFFFFFFFUL) return 12;
 x ^= 0x80000000UL;
 if (x != 0x7FFFFFFFUL) return 13;
 x *= 2UL;
 if (x != 0xFFFFFFFEUL) return 14;
 return 42;
}
