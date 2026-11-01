struct node{int value;struct node *next;}; int main(void){struct node n; n.next=&n; return 0;}
