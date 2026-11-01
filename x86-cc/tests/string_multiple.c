int first(char *p) { return *p; }
int main(void) {
    return first("(") + first("two") - 114;
}
