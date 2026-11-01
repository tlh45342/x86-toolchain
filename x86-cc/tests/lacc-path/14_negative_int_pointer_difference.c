int main(void) {
 int a[5];
 int *p;
 int *q;
 p = &a[4];
 q = &a[1];
 if (q-p != -3) return 11;
 if (p-q != 3) return 12;
 return 42;
}
