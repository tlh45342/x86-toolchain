struct region { int seg; int off; };
struct loaded { struct region code; struct region data; };
int main(void)
{
 struct loaded x;
 struct loaded *p;
 p=&x;
 p->code.seg=42;
 p->code.off=7;
 x.data.seg=11;
 if(p->code.seg!=42) return 1;
 if(p->code.off!=7) return 2;
 if(x.data.seg!=11) return 3;
 return 42;
}
