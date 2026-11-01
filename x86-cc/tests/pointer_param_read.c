int read_value(int *p) {
    return *p;
}

int main(void) {
    int x = 42;
    return read_value(&x);
}
