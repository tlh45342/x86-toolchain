int helper(void) { return 0; }
int main(int argc, char **argv) {
    if (argc == 2 && argv[1][0] == 'x')
        return 42;
    return helper();
}
