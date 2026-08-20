#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "headers/merge_sort.h"
#include "headers/quick_sort.h"
#include "shared/comparable.h"
#include "shared/record.h"

#define LINE_BUFFER_SIZE 256
#define FIELD1_SIZE 64

static int is_blank_line(const char *line)
{
    return strspn(line, " \t\r\n") == strlen(line);
}

static size_t count_records(FILE *input)
{
    char line[LINE_BUFFER_SIZE];
    size_t count = 0;

    while (fgets(line, sizeof(line), input) != NULL)
    {
        if (!is_blank_line(line))
            count++;
    }

    rewind(input);
    return count;
}

static void free_records(struct Record *records, size_t count)
{
    if (records == NULL)
        return;

    for (size_t i = 0; i < count; i++)
        free(records[i].field1);

    free(records);
}

static Compar comparator_for_field(size_t field)
{
    switch (field)
    {
    case 1:
        return compare_records_string;
    case 2:
        return compare_records_int;
    case 3:
        return compare_records_float;
    default:
        return NULL;
    }
}

void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo)
{
    Compar comparator = comparator_for_field(field);
    if (infile == NULL || outfile == NULL || comparator == NULL || (algo != 1 && algo != 2))
    {
        fprintf(stderr, "Parametri di ordinamento non validi.\n");
        exit(EXIT_FAILURE);
    }

    size_t record_count = count_records(infile);
    if (record_count == 0)
        return;

    struct Record *records = calloc(record_count, sizeof(*records));
    if (records == NULL)
    {
        perror("Impossibile allocare la memoria per i record");
        exit(EXIT_FAILURE);
    }

    char line[LINE_BUFFER_SIZE];
    size_t loaded = 0;
    size_t line_number = 0;
    while (loaded < record_count && fgets(line, sizeof(line), infile) != NULL)
    {
        line_number++;
        if (is_blank_line(line))
            continue;

        char field1[FIELD1_SIZE];
        int parsed = sscanf(
            line,
            "%d,%63[^,],%d,%f",
            &records[loaded].id,
            field1,
            &records[loaded].field2,
            &records[loaded].field3);

        if (parsed != 4)
        {
            fprintf(stderr, "Record CSV non valido alla riga %zu.\n", line_number);
            free_records(records, loaded);
            exit(EXIT_FAILURE);
        }

        size_t field1_length = strlen(field1) + 1;
        records[loaded].field1 = malloc(field1_length);
        if (records[loaded].field1 == NULL)
        {
            perror("Impossibile allocare la memoria per field1");
            free_records(records, loaded);
            exit(EXIT_FAILURE);
        }
        memcpy(records[loaded].field1, field1, field1_length);
        loaded++;
    }

    printf("Record caricati: %zu\n", loaded);
    if (algo == 1)
        TIMING(merge_sort_wrapper(records, loaded, sizeof(records[0]), comparator));
    else
        TIMING(quick_sort(records, loaded, sizeof(records[0]), comparator));

    for (size_t i = 0; i < loaded; i++)
    {
        fprintf(
            outfile,
            "%d,%s,%d,%f\n",
            records[i].id,
            records[i].field1,
            records[i].field2,
            records[i].field3);
    }

    free_records(records, loaded);
}

static int parse_option(const char *text, long minimum, long maximum, size_t *result)
{
    char *end = NULL;
    errno = 0;
    long value = strtol(text, &end, 10);

    if (errno != 0 || end == text || *end != '\0' || value < minimum || value > maximum)
        return 0;

    *result = (size_t)value;
    return 1;
}

int main(int argc, char const *argv[])
{
    if (argc != 5)
    {
        fprintf(
            stderr,
            "Uso: %s <input.csv> <output.csv> <campo: 1-3> <algoritmo: 1-2>\n",
            argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], argv[2]) == 0)
    {
        fprintf(stderr, "Il file di output deve essere diverso dal file di input.\n");
        return EXIT_FAILURE;
    }

    size_t field;
    size_t algorithm;
    if (!parse_option(argv[3], 1, 3, &field) || !parse_option(argv[4], 1, 2, &algorithm))
    {
        fprintf(stderr, "Campo o algoritmo non valido.\n");
        return EXIT_FAILURE;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        perror("Impossibile aprire il file di input");
        return EXIT_FAILURE;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        perror("Impossibile aprire il file di output");
        fclose(input);
        return EXIT_FAILURE;
    }

    sort_records(input, output, field, algorithm);

    fclose(input);
    fclose(output);
    return EXIT_SUCCESS;
}
