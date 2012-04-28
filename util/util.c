#include <stdio.h>

#include "util.h"

int
cmp_int(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

void
print_addr(void *elem, void *unused)
{
    printf("%p->", *(void **)elem);
}

void
print_double(void *elem, void *unused)
{
    printf("%.2f->", *(double *)elem);
}

void
print_int(void *elem, void *unused)
{
    printf("%d->", *(int *)elem);
}