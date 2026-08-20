
#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>

void merge(void *base, size_t l, size_t m, size_t r, size_t size, int (*compar)(const void *, const void *));

void merge_sort(void *base, size_t l, size_t r, size_t size, int (*compar)(const void *, const void *));

void merge_sort_wrapper(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *));

#endif
