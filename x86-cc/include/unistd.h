#ifndef _UNISTD_H
#define _UNISTD_H
#include <sys/types.h>

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

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

#endif
