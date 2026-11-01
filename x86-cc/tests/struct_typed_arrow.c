struct Item {
    char tag;
    char *text;
};

int main(void) {
    struct Item x;
    struct Item *p = &x;
    p->tag = 42;
    p->text = "x";
    return p->tag;
}
