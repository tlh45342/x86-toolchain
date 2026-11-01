/* A cast to a typedef is not a declaration and must not skip later locals. */
typedef unsigned int size_t;
typedef int ssize_t;
int main(void)
{
    char buffer[32];
    int n = 3;
    while (n < (size_t)4) {
        ssize_t written = n;
        buffer[0] = written;
        n = 4;
    }
    return buffer[0];
}
