struct inode {
    unsigned short ino;
    unsigned short mode;
    unsigned long size;
    unsigned long direct[12];
    struct inode *next;
};

int main(void)
{
    struct inode n;
    struct inode *p;
    p = &n;
    p->ino = 2;
    p->mode = 7;
    p->size = 4096UL;
    p->direct[3] = 42UL;
    p->next = &n;
    if (sizeof(struct inode) != 58)
        return 1;
    if (p->direct[3] != 42UL)
        return 2;
    if (p->next->ino != 2)
        return 3;
    return 0;
}
