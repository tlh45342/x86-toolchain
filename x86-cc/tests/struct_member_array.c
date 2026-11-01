struct box {
    char pad[4];
    int value;
};
int main(void)
{
    struct box b;
    b.value = 42;
    return b.value;
}
