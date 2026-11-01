int read(int **pp) {
    return **pp;
}
int main(void) {
    int x = 42;
    int *p = &x;
    return read(&p);
}
