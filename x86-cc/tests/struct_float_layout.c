struct fpbox {
    char lead;
    float f;
    double d;
    int tail;
};
int main(void)
{
    struct fpbox x;
    x.tail = 42;
    return x.tail;
}
