/* LACC c89/function-pointer.c inspired direct callback-member assignment. */
struct action { void (*callback)(int); int flags; };
static void handler(int signo) { (void)signo; }
int main(void) {
    struct action sa;
    sa.callback = handler;
    sa.flags = 7;
    return sa.flags;
}
