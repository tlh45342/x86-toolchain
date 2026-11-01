typedef void (*handler_t)(int);
struct action { handler_t callback; int flags; };
static void handler(int signo) { (void)signo; }
int main(void) { struct action sa; sa.callback = handler; sa.flags = 7; return sa.flags; }
