/* LACC cast-function.c inspired function-pointer typedef cast. */
typedef void (*handler_t)(int);
int signal_probe(int signo, handler_t handler);
int main(void)
{
    return signal_probe(13, (handler_t)1);
}
