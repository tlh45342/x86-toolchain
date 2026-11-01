struct item {
    int tag;
    union {
        int number;
        char bytes[4];
    } u;
};
int main(void)
{
    struct item x;
    x.tag = 42;
    return x.tag;
}
