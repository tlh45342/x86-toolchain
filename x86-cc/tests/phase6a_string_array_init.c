static char a[] = "Hello";
static char b[8] = "abc";
static char c[3] = "abc";
int main(void) {
 if(a[0]!='H') return 1;
 if(a[5]!=0) return 2;
 if(b[3]!=0) return 3;
 if(b[7]!=0) return 4;
 if(c[2]!='c') return 5;
 return 0;
}
