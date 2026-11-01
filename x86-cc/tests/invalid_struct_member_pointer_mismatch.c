struct Holder { int *p; };
int main(void) { char c = 42; struct Holder h; h.p = &c; return 0; }
