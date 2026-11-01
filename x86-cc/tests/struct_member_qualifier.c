struct qualified {
    char const *name;
    volatile int value;
};
int main(void)
{
    struct qualified x;
    x.value = 42;
    return x.value;
}
