int value;
int data[2];

int main(void)
{
    value = 40;
    value++;
    data[0] = 1;
    data[0]++;
    return value + data[0] - 1;
}
