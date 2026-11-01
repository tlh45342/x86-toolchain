static unsigned short far *screen=(unsigned short far *)0xB8000000UL;
unsigned short far_read(int i)
{
    return screen[i+80];
}
void far_copy(int i)
{
    screen[i]=screen[i+80];
}
