#ifndef _STDIO_H
#define _STDIO_H
#include <stdarg.h>
#include <stddef.h>
#define EOF (-1)
int printf(const char *fmt, ...);
int sprintf(char *out, const char *fmt, ...);
int vprintf(const char *fmt, va_list ap);
int vsprintf(char *out, const char *fmt, va_list ap);
int snprintf(char *out, size_t size, const char *fmt, ...);
int vsnprintf(char *out, size_t size, const char *fmt, va_list ap);
int puts(const char *s);
int putchar(int c);
void perror(const char *message);
#endif
