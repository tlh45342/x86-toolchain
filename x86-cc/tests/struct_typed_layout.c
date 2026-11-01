struct Item {
    char tag;
    int value;
    char tail;
};

int main(void) {
    struct Item x;
    x.tag = 1;
    x.value = 42;
    x.tail = 2;
    return x.value;
}
