struct inode { unsigned short ino; struct inode *next; }; int main(void){struct inode n; struct inode *p; p=&n; p->next=&n; return 0;}
