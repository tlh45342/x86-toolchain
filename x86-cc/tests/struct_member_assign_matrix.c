struct inode { int ino; int mode; };
struct file { int used; struct inode inode; };
struct file files[4];
int main(void) {
 struct inode a,b;
 a.ino=2; a.mode=7;
 b=a;
 files[2].inode=b;
 a=files[2].inode;
 return a.ino;
}
