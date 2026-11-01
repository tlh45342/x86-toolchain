int main(void) {
 unsigned long a[3];
 unsigned long *p;
 unsigned long *q;
 a[0]=11UL; a[1]=42UL; a[2]=99UL;
 p=&a[0];
 q=p++;
 if (q != &a[0]) return 11;
 if (p != &a[1]) return 12;
 if (*p != 42UL) return 13;
 p++;
 if (p != &a[2]) return 14;
 p--;
 if (p != &a[1]) return 15;
 return 42;
}
