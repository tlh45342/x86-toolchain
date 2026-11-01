static unsigned short far *video = (unsigned short far *)0xB8000000UL;
void far_vga_probe(void)
{
    video[0] = 0x0748;
    video[1] = 0x0765;
}
