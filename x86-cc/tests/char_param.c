int read(char *p) { return *p; }
int main(void) { char c=42; return read(&c); }
