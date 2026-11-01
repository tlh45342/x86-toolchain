int main(void) {
    char buf[512];
    buf[0] = 40;
    buf[511] = 2;
    return buf[0] + buf[511];
}
