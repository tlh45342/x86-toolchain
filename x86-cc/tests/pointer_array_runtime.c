int read(int **p, int i) {
    return *p[i];
}
int main(void) {
    int a = 7;
    int b = 42;
    int *items[2];
    items[0] = &a;
    items[1] = &b;
    return read(items, 1);
}
