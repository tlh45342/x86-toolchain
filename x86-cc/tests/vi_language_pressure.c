int helper(void){return 1;}
int main(void){int a=0,b=0;char buf[4];do{a++;}while(a<2);b=1|2;if((b=3))a+=sizeof(buf);switch(a){case 6:a=40;break;default:a=0;}a=a?a+2:0;(void)helper();return a;}
