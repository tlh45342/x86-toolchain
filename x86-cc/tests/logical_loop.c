int main(void) {
    int i = 0;
    int sum = 0;
    while (i < 6 && sum < 42) {
        sum = sum + 7;
        i = i + 1;
    }
    return sum;
}
