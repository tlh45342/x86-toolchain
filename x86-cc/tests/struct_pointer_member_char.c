struct Holder {
    char *p;
};

int main(void) {
    struct Holder h;
    h.p = "*";
    return *h.p;
}
