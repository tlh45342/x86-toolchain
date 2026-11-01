#ifndef _STDLIB_H
#define _STDLIB_H
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/* Decimal string conversion provided by the target C library. */
int atoi(const char *text);
char *getenv(const char *name);

#endif
