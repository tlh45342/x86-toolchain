int main(void) {
    int x = 42;
    int *items[2];
    items[0] = &x;
    items[1] = &x;
    return *items[1];
}
