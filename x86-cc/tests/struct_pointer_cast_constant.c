struct node { int value; struct node *next; };
int main(void)
{
 struct node *p;
 p=(struct node *)0xA000;
 if(p==(struct node *)0xA000) return 42;
 return 0;
}
