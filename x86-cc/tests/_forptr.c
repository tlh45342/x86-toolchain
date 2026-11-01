struct node { int value; struct node *next; };
static struct node a;
static struct node b;
int main(void)
{
 struct node *p;
 p=&a;
 p->next=&b;
 for(p=&a;p && p->next;p=p->next) p->value=42;
 return p->value;
}
