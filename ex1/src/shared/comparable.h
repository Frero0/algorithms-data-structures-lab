#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TIMING(a)                                                       \
  do                                                                    \
  {                                                                     \
    clock_t start = clock();                                            \
    a;                                                                  \
    clock_t end = clock();                                              \
    printf("%s: %f sec\n", #a, (double)(end - start) / CLOCKS_PER_SEC); \
  } while (0)

#define ISCANF(a, b)                     \
  do                                     \
  {                                      \
    int ignored __attribute__((unused)); \
    ignored = scanf(a, b);               \
  } while (0)

typedef int (*Compar)(const void *a, const void *b);

int compare_int(const void *a, const void *b);

int compare_char(const void *a, const void *b);

int compare_double(const void *a, const void *b);

int compare_string(const void *a, const void *b);

int compare_long(const void *a, const void *b);

int compare_float(const void *a, const void *b);
