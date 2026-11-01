int main(void) {
    int n = 40;
    {
        int x = 1;
        n = n + x;
    }
    {
        int x = 1;
        n = n + x;
    }
    return n;
}
