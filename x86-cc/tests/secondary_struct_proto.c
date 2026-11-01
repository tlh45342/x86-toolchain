struct cpu_context {
 int sp; int bx; int cx; int dx; int si; int di; int bp; int es; int ss;
};
struct process_image {
 unsigned int code_seg; unsigned int code_size;
 unsigned int data_seg; unsigned int data_size;
 unsigned int stack_seg; unsigned int stack_size;
};
struct process {
 int pid; int ppid; int state; int exit_status;
 struct cpu_context context;
 unsigned int code_seg; unsigned int code_size;
 unsigned int data_seg; unsigned int data_size;
 unsigned int stack_seg; unsigned int stack_size;
};
int process_set_image(int pid,struct process_image *image);
int process_set_image(int pid,struct process_image *image)
{
 return pid + image->code_seg;
}
int main(void)
{
 struct process_image image;
 image.code_seg=2;
 return process_set_image(40,&image);
}
