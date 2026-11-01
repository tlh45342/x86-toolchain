#ifndef B_H
#define B_H
#include "a.h"
struct context { int sp; int bx; int cx; int dx; int si; int di; int bp; int es; int ss; };
struct image { struct region code; struct region data; struct region stack; };
struct process { int pid; struct context context; struct image image; };
int set_image(int pid,struct image *image);
#endif
