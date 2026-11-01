int main(void) {
 int a;
 a = 0x33;
 a &= 0x11;
 if (a != 0x11) return 11;
 return 42;
}
