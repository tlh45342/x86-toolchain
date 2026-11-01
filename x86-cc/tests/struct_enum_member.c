enum kind { K_ZERO, K_ONE };
struct item {
    enum kind kind;
    int value;
};
int main(void)
{
    struct item x;
    x.value = 42;
    return x.value;
}
