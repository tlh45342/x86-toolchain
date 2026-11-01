struct Holder { char *p; };
int main(void) { int x = 42; struct Holder h; h.p = &x; return 0; }
