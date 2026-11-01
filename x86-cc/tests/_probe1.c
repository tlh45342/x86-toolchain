struct inode { unsigned short ino; unsigned long size; }; int main(void){struct inode n; n.ino=2; return n.ino;}
