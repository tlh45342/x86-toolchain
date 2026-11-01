struct node { int value; struct node *next; };
static struct node a;
static struct node b;
int main(void)
{
 struct node *p;
 p=&a;
 p->next=&b;
 b.next=0;
 for(p=&a;p && p->next;p=p->next) p->value=42;
 p=&a;
 return p->value;
}
