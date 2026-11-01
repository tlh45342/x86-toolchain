struct node { int value; struct node *next; };
static struct node a;
static struct node b;
static struct node *head;
int main(void)
{
 head=&a;
 head->next=&b;
 head->next->value=42;
 return head->next->value;
}
