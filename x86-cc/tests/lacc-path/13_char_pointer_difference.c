int main(void) {
 char a[6];
 char *p;
 char *q;
 p = &a[1];
 q = &a[5];
 if (q-p != 4) return 11;
 if (p-q != -4) return 12;
 return 42;
}
