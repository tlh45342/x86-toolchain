struct Item {
    char tag;
    int value;
};

int main(void) {
    struct Item x;
    x.tag = 42;
    x.value = 1;
    return x.tag;
}
