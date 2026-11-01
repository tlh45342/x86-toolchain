unsigned long sink32;
unsigned int sink16;

void exercise(unsigned long x)
{
    unsigned int u;
    unsigned long y;
    u = 12;
    y = 0x12345678UL;
    y = x + 1;
    y = y - 2;
    y = y >> 8;
    y = y << 3;
    sink16 = (unsigned int)y;
    sink32 = y;
}

int main(void)
{
    exercise(0x12345678UL);
    return 0;
}
