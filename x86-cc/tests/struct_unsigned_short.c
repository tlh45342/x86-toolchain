struct inode { unsigned short ino; unsigned short mode; };
int main(void) {
    struct inode n;
    n.ino = 2;
    n.mode = 7;
    if (sizeof(struct inode) != 4) return 1;
    return n.ino + n.mode;
}
