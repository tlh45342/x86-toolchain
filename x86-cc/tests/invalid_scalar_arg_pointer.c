int identity(int x) { return x; }
int main(void) { int x = 42; return identity(&x); }
