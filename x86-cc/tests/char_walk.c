int sum(char *p, int n) { int s=0; int i=0; while(i<n) { s=s+*(p+i); i=i+1; } return s; }
int main(void) { char a[3]; a[0]=10; a[1]=20; a[2]=12; return sum(a,3); }
