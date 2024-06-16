#ifndef edit_distance_h
#define edit_distance_h

#include <stdio.h>

int edit_distance(char *s1, char *s2, int, int);

int edit_distance_dyn(char *s1, char *s2);

int edit_distance_rec(char *str1, char *str2, int i, int j, int **memo);

int min(int, int);

int min1(int x, int y, int z);

#endif