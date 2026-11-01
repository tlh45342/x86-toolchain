int f(unsigned long lba){if((lba>>24)!=0)return -5;return (unsigned int)(lba>>8);} int main(void){return 0;}
