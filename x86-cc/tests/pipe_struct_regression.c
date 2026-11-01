struct pair { unsigned char kind; unsigned char index; };
int check_struct(void) { struct pair a,b; a.kind=2; a.index=7; b=a; return b.kind==2 && b.index==7; }
int main(void) { return check_struct() ? 42 : 1; }
