#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(void *a, void *b, size_t size);

size_t partition(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *));

void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *));

#endif
