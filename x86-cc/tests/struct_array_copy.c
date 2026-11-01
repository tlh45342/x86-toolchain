struct inode { unsigned short ino; unsigned short mode; unsigned long size; };
struct file { int used; struct inode inode; unsigned long pos; };
static struct file files[8];

int main(void)
{
    struct inode n;
    int i;
    i = 3;
    n.ino = 2;
    n.mode = 7;
    n.size = 4096UL;
    files[i].used = 1;
    files[i].inode = n;
    files[i].pos = 12UL;
    if (files[i].inode.ino != 2) return 1;
    return 0;
}
