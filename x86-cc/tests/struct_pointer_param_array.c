struct E { char text[16]; int len; }; int first(struct E *e, int i) { return e->text[i]; } int main(void) { struct E e; struct E *p; p=&e; p->text[1]=42; return first(p,1); }
