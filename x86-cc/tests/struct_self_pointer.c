struct node {
    struct node *next;
    int value;
};
int main(void)
{
    struct node x;
    x.value = 42;
    return x.value;
}
