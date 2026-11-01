int main(void) {
 int a;
 a = 0x03;
 a |= 0x10;
 if (a != 0x13) return 11;
 return 42;
}
