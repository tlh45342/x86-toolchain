int main(void) {
    char *p = "*";
    char **pp = &p;
    return **pp;
}
