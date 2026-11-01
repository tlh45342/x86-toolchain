static void out8(unsigned int port,unsigned int value){asm { mov dx, [bp+4] mov ax, [bp+6] out dx, al }} int main(void){return 0;}
