/* Reduced from Blackjack local/shell.c builtin(). Valid C. */
int printf(const char *fmt, ...);
int sprintf(char *out, const char *fmt, ...);
int vprintf(const char *fmt, char * ap);
int vsprintf(char *out, const char *fmt, char * ap);
int snprintf(char *out, size_t size, const char *fmt, ...);
int vsnprintf(char *out, size_t size, const char *fmt, char * ap);
int puts(const char *s);
int putchar(int c);

/* Decimal string conversion provided by the target C library. */
int atoi(const char *text);

size_t strlen(const char *s);
int strcmp(const char *a, const char *b);
int strncmp(const char *a, const char *b, size_t n);
char *strcpy(char *d, const char *s);
char *strncpy(char *d, const char *s, size_t n);
char *strcat(char *d, const char *s);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
void *memcpy(void *d, const void *s, size_t n);
void *memmove(void *d, const void *s, size_t n);
void *memset(void *d, int c, size_t n);
int memcmp(const void *a, const void *b, size_t n);





ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int close(int fd);
int chdir(const char *path);
unsigned int sleep(unsigned int seconds);
int geteuid(void);
int unlink(const char *path);
int link(const char *oldpath, const char *newpath);
int rename(const char *oldpath, const char *newpath);
int isatty(int fd);
char *getcwd(char *buf, size_t size);
ssize_t readlink(const char *path, char *buf, size_t size);

static char cwd[128];
static int builtin(char **argv, int in_child)
{
    if (!argv[0]) return 1;
    if (strcmp(argv[0], "exit") == 0) return in_child ? 1 : -1;
    if (strcmp(argv[0], "pwd") == 0) { puts(cwd); return 1; }
    if (strcmp(argv[0], "cd") == 0) {
        const char *dest = argv[1] ? argv[1] : getenv("HOME");
        if (!dest) dest = "/";
        if (chdir(dest) < 0) {
            perror("cd");
        } else if (!getcwd(cwd, sizeof(cwd))) {
            strncpy(cwd, dest, sizeof(cwd) - 1);
            cwd[sizeof(cwd) - 1] = 0;
        }
        return 1;
    }
    return 0;
}
int main(void) { char *a[2] = {"pwd", 0}; return builtin(a, 0); }
