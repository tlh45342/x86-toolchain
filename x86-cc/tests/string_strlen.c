int length(char *p) {
    int n = 0;
    while (*p) {
        n = n + 1;
        p = p + 1;
    }
    return n;
}
int main(void) {
    return length("..........................................");
}
