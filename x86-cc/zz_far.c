static unsigned short far *video = (unsigned short far *)0xB8000000UL;
void poke(void) { video[1] = 0x0748; }
