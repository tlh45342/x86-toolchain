/* Regression: frame prepass must match generated local storage. */
typedef unsigned int socklen_t;
int main(void)
{
    unsigned char packet[8];
    unsigned char reply[64];
    unsigned char address[16];
    socklen_t addrlen;
    int fd;
    int rc;
    packet[0] = 1;
    reply[0] = 2;
    address[0] = 3;
    addrlen = 4;
    fd = 5;
    rc = 27;
    return packet[0] + reply[0] + address[0] + addrlen + fd + rc;
}
