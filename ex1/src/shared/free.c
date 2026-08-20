#include "free.h"

void free_string(void *a)
{
  free(*(char **)a);
}
