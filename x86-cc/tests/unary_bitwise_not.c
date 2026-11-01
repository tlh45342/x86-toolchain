int main(void)
{
 int x;
 x=0x00ff;
 if((~x & 0xffff)!=0xff00) return 1;
 if(~~42!=42) return 2;
 return 42;
}
