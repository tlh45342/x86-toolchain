struct node { int value; struct node *next; };
static struct node a;
static struct node *head;
int main(void){ head=&a; head->value=42; head->next=0; return head->value; }
