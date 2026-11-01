int fetch(int *);

int main(void) {
    int x = 42;
    return fetch(&x);
}

int fetch(int *p) {
    return *p;
}
