#define CAP 64u
char text[CAP];
int main(void) {
    text[7] = 42U;
    return text[7];
}
