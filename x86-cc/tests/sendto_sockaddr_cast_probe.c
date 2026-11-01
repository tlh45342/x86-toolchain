#include <sys/socket.h>
int test(int fd, unsigned char *dst) { return sendto(fd, dst, 8, 0, (const struct sockaddr *)dst, 16); }
