int main(void) {
 int a[4];
 int *p;
 int *q;
 p = &a[0];
 q = &a[3];
 if (q - p != 3) return 11;
 return 42;
}
