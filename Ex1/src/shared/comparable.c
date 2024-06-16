#include "comparable.h"

int compare_int(const void *a, const void *b)
{
    if (a == NULL)
    {
        printf("valore di a non valido in compare int\n");
        exit(EXIT_FAILURE);
    }
    if (b == NULL)
    {
        printf("valore di b non valido in compare int\n");
        exit(EXIT_FAILURE);
    }
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2)
        return -1;
    if (arg1 > arg2)
        return 1;
    return 0;
}

int compare_char(const void *a, const void *b)
{
    if (a == NULL)
    {
        printf("valore di a non valido in compare int\n");
        exit(EXIT_FAILURE);
    }
    if (b == NULL)
    {
        printf("valore di b non valido in compare int\n");
        exit(EXIT_FAILURE);
    }

    char v1 = *(char *)a;
    char v2 = *(char *)b;
    if (v1 < v2)
        return -1;
    if (v1 > v2)
        return 1;
    return 0;
}

int compare_double(const void *a, const void *b)
{
    if (a == NULL)
    {
        printf("valore di a non valido in compare double\n");
        exit(EXIT_FAILURE);
    }
    if (b == NULL)
    {
        printf("valore di b non valido in compare double\n");
        exit(EXIT_FAILURE);
    }
    double v1 = *(const double *)a;
    double v2 = *(const double *)b;
    if (v1 < v2)
        return -1;
    if (v1 > v2)
        return 1;
    return 0;
}

int compare_float(const void *a, const void *b)
{
    if (a == NULL)
    {
        printf("valore di a non valido in compare float\n");
        exit(EXIT_FAILURE);
    }
    if (b == NULL)
    {
        printf("valore di b non valido in compare float\n");
        exit(EXIT_FAILURE);
    }
    float arg1 = *(const float *)a;
    float arg2 = *(const float *)b;

    if (arg1 < arg2)
        return -1;
    if (arg1 > arg2)
        return 1;
    return 0;
}

int compare_long(const void *a, const void *b)
{
    if (a == NULL)
    {
        printf("valore di a non valido in compare long\n");
        exit(EXIT_FAILURE);
    }
    if (b == NULL)
    {
        printf("valore di b non valido in compare long\n");
        exit(EXIT_FAILURE);
    }
    long v1 = *(long *)a;
    long v2 = *(long *)b;
    if (v1 < v2)
        return -1;
    if (v1 > v2)
        return 1;
    return 0;
}

int compare_string(const void *a, const void *b)
{
    if (a == NULL)
    {
        printf("valore di a non valido in compare string\n");
        exit(EXIT_FAILURE);
    }
    if (b == NULL)
    {
        printf("valore di b non valido in compare string\n");
        exit(EXIT_FAILURE);
    }
    return strcmp(*(const char **)a, *(const char **)b);
}
