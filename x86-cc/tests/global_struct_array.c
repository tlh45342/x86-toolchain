struct E { char a[8]; int n; };
struct E g;
int main(void) { struct E *p=&g; p->a[0]='A'; p->a[1]='B'; p->n=40; return p->a[0]+p->a[1]-p->n-89; }
