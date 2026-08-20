#ifndef EDIT_DISTANCE_H
#define EDIT_DISTANCE_H

#include <stddef.h>

int edit_distance(const char *first, const char *second, size_t first_length, size_t second_length);

int edit_distance_dyn(const char *first, const char *second);

#endif
