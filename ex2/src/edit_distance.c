#include "edit_distance.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static int minimum(int first, int second)
{
    return first < second ? first : second;
}

static int minimum_of_three(int first, int second, int third)
{
    return minimum(minimum(first, second), third);
}

int edit_distance(const char *first, const char *second, size_t first_length, size_t second_length)
{
    if (first == NULL || second == NULL)
        return -1;
    if (first_length == 0)
        return (int)second_length;
    if (second_length == 0)
        return (int)first_length;

    int no_operation = first[0] == second[0]
                           ? edit_distance(first + 1, second + 1, first_length - 1, second_length - 1)
                           : (int)(first_length + second_length);
    int cancellation = 1 + edit_distance(first, second + 1, first_length, second_length - 1);
    int insertion = 1 + edit_distance(first + 1, second, first_length - 1, second_length);

    return minimum_of_three(no_operation, cancellation, insertion);
}

static size_t memo_index(size_t row, size_t column, size_t columns)
{
    return row * columns + column;
}

static int edit_distance_memoized(
    const char *first,
    const char *second,
    size_t first_length,
    size_t second_length,
    size_t columns,
    int *memo)
{
    size_t index = memo_index(first_length, second_length, columns);
    if (memo[index] != -1)
        return memo[index];

    if (first_length == 0)
        memo[index] = (int)second_length;
    else if (second_length == 0)
        memo[index] = (int)first_length;
    else if (first[first_length - 1] == second[second_length - 1])
        memo[index] = edit_distance_memoized(
            first,
            second,
            first_length - 1,
            second_length - 1,
            columns,
            memo);
    else
        memo[index] = 1 + minimum(
                              edit_distance_memoized(
                                  first,
                                  second,
                                  first_length,
                                  second_length - 1,
                                  columns,
                                  memo),
                              edit_distance_memoized(
                                  first,
                                  second,
                                  first_length - 1,
                                  second_length,
                                  columns,
                                  memo));

    return memo[index];
}

int edit_distance_dyn(const char *first, const char *second)
{
    if (first == NULL || second == NULL)
        return -1;

    size_t first_length = strlen(first);
    size_t second_length = strlen(second);
    size_t rows = first_length + 1;
    size_t columns = second_length + 1;

    if (rows > SIZE_MAX / columns || rows * columns > SIZE_MAX / sizeof(int))
        return -1;

    size_t cell_count = rows * columns;
    int *memo = malloc(cell_count * sizeof(*memo));
    if (memo == NULL)
        return -1;

    for (size_t i = 0; i < cell_count; i++)
        memo[i] = -1;

    int result = edit_distance_memoized(
        first,
        second,
        first_length,
        second_length,
        columns,
        memo);

    free(memo);
    return result;
}
