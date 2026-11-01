static int first(const char *p) {
    return p[0];
}

int main(void) {
    const char *p = "*";
    return first(p);
}
