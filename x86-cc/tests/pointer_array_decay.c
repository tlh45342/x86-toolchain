int pick(char **p) {
    return *p[1];
}
int main(void) {
    char *words[2];
    words[0] = "x";
    words[1] = "*";
    return pick(words);
}
