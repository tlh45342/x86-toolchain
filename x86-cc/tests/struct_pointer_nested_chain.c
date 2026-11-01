struct node { int value; struct node *next; };
static struct node a;
static struct node b;
static struct node c;
int main(void)
{
 struct node *p;
 p=&a;
 p->next=&b;
 b.next=&c;
 c.value=35;
 p->value=p->next->next->value+7;
 return p->value;
}
