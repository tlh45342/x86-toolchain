int main(void) { int i=0; int n=0; int j=0; for (i=0; i<6; i=i+1) { for (j=0; j<8; j=j+1) { if (j<7) continue; n=n+1; } } return n*7; }
