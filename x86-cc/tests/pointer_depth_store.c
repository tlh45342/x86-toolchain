int main(void) {
    int x = 0;
    int *p = &x;
    int **pp = &p;
    **pp = 42;
    return x;
}
