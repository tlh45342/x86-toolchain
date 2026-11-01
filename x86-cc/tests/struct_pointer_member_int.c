struct Holder {
    int *p;
};

int main(void) {
    int x = 42;
    struct Holder h;
    h.p = &x;
    return *h.p;
}
