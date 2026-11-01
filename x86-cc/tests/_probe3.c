struct inode { unsigned short ino; unsigned long direct[12]; }; int main(void){struct inode n; n.direct[3]=42UL; return 0;}
