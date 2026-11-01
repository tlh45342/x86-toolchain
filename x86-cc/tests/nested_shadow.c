int main(void) {
    int x = 40;
    {
        int x = 10;
        {
            int x = 2;
            x = x + 5;
        }
        x = x + 1;
    }
    return x + 2;
}
