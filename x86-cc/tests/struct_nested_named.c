struct inner {
    int value;
};
struct outer {
    char lead;
    struct inner item;
    int tail;
};
int main(void)
{
    struct outer x;
    x.tail = 42;
    return x.tail;
}
