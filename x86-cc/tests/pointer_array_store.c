int main(void) {
    int a = 1;
    int b = 42;
    int *items[2];
    items[0] = &a;
    items[1] = &b;
    *items[0] = *items[1];
    return a;
}
