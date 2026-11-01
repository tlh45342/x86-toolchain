/* POSIX-style one-shot ICMP echo client for Blackjack. */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

static int parse_octet(const char *s, int *pos, unsigned char *out)
{
    int value, digits;
    value = 0;
    digits = 0;
    while (s[*pos] >= '0' && s[*pos] <= '9') {
        value = value * 10 + s[*pos] - '0';
        if (value > 255 || digits >= 3)
            return -1;
        *pos = *pos + 1;
        digits = digits + 1;
    }
    if (!digits)
        return -1;
    *out = value;
    return 0;
}

static int parse_ipv4(const char *s, unsigned char *out)
{
    int i, pos;
    pos = 0;
    for (i = 0; i < 4; i = i + 1) {
        if (parse_octet(s, &pos, &out[i]) < 0)
            return -1;
        if (i < 3) {
            if (s[pos] != '.')
                return -1;
            pos = pos + 1;
        }
    }
    return s[pos] ? -1 : 0;
}

static void message(const char *s)
{
    int n;
    n = 0;
    while (s[n])
        n = n + 1;
    write(1, s, n);
}

int main(int argc, char **argv)
{
    unsigned char dst[16];
    unsigned char src[16];
    unsigned char packet[8];
    unsigned char reply[64];
    unsigned char *address;
    socklen_t addrlen;
    int fd;
    int rc;
    return 0;
}
