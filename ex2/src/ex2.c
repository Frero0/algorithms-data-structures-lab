#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "edit_distance.h"

#define WORD_BUFFER_SIZE 1024
#define TEXT_BUFFER_SIZE 4096

struct Dictionary
{
    char **words;
    size_t count;
    size_t capacity;
};

struct ClosestWords
{
    const char **items;
    size_t count;
    size_t capacity;
    int distance;
};

static char *copy_string(const char *text)
{
    size_t length = strlen(text) + 1;
    char *copy = malloc(length);
    if (copy != NULL)
        memcpy(copy, text, length);
    return copy;
}

static void remove_line_ending(char *text)
{
    text[strcspn(text, "\r\n")] = '\0';
}

static void normalize_ascii(char *text)
{
    for (size_t i = 0; text[i] != '\0'; i++)
        text[i] = (char)tolower((unsigned char)text[i]);
}

static int compare_words(const void *first, const void *second)
{
    const char *const *first_word = first;
    const char *const *second_word = second;
    return strcmp(*first_word, *second_word);
}

static int dictionary_add(struct Dictionary *dictionary, const char *word)
{
    if (dictionary->count == dictionary->capacity)
    {
        size_t new_capacity = dictionary->capacity == 0 ? 4096 : dictionary->capacity * 2;
        if (new_capacity < dictionary->capacity)
            return 0;

        char **new_words = realloc(dictionary->words, new_capacity * sizeof(*new_words));
        if (new_words == NULL)
            return 0;

        dictionary->words = new_words;
        dictionary->capacity = new_capacity;
    }

    dictionary->words[dictionary->count] = copy_string(word);
    if (dictionary->words[dictionary->count] == NULL)
        return 0;

    dictionary->count++;
    return 1;
}

static void dictionary_free(struct Dictionary *dictionary)
{
    for (size_t i = 0; i < dictionary->count; i++)
        free(dictionary->words[i]);
    free(dictionary->words);
}

static int dictionary_load(const char *path, struct Dictionary *dictionary)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        perror("Impossibile aprire il dizionario");
        return 0;
    }

    char word[WORD_BUFFER_SIZE];
    while (fgets(word, sizeof(word), file) != NULL)
    {
        remove_line_ending(word);
        normalize_ascii(word);
        if (word[0] != '\0' && !dictionary_add(dictionary, word))
        {
            fprintf(stderr, "Memoria insufficiente durante il caricamento del dizionario.\n");
            fclose(file);
            return 0;
        }
    }

    if (ferror(file))
    {
        perror("Errore durante la lettura del dizionario");
        fclose(file);
        return 0;
    }

    fclose(file);
    qsort(dictionary->words, dictionary->count, sizeof(*dictionary->words), compare_words);
    return 1;
}

static void closest_words_reset(struct ClosestWords *closest)
{
    closest->count = 0;
    closest->distance = INT_MAX;
}

static int closest_words_add(struct ClosestWords *closest, const char *word)
{
    if (closest->count == closest->capacity)
    {
        size_t new_capacity = closest->capacity == 0 ? 8 : closest->capacity * 2;
        if (new_capacity < closest->capacity)
            return 0;

        const char **new_items = realloc(closest->items, new_capacity * sizeof(*new_items));
        if (new_items == NULL)
            return 0;

        closest->items = new_items;
        closest->capacity = new_capacity;
    }

    closest->items[closest->count++] = word;
    return 1;
}

static size_t length_difference(size_t first, size_t second)
{
    return first > second ? first - second : second - first;
}

static int find_closest_words(
    const struct Dictionary *dictionary,
    const char *target,
    struct ClosestWords *closest)
{
    closest_words_reset(closest);

    const char *key = target;
    char **exact = bsearch(
        &key,
        dictionary->words,
        dictionary->count,
        sizeof(*dictionary->words),
        compare_words);
    if (exact != NULL)
    {
        closest->distance = 0;
        return closest_words_add(closest, *exact);
    }

    size_t target_length = strlen(target);
    for (size_t i = 0; i < dictionary->count; i++)
    {
        const char *candidate = dictionary->words[i];
        size_t difference = length_difference(target_length, strlen(candidate));
        if (closest->distance != INT_MAX && difference > (size_t)closest->distance)
            continue;

        int distance = edit_distance_dyn(target, candidate);
        if (distance < 0)
            return 0;

        if (distance < closest->distance)
        {
            closest->count = 0;
            closest->distance = distance;
        }
        if (distance == closest->distance && !closest_words_add(closest, candidate))
            return 0;
    }

    return closest->count > 0;
}

static void print_closest_words(const char *word, const struct ClosestWords *closest)
{
    printf("%s -> ", word);
    for (size_t i = 0; i < closest->count; i++)
    {
        if (i > 0)
            printf(", ");
        printf("%s", closest->items[i]);
    }
    printf(" (distanza: %d)\n", closest->distance);
}

static int correct_text(
    const char *path,
    const struct Dictionary *dictionary,
    struct ClosestWords *closest)
{
    FILE *text = fopen(path, "r");
    if (text == NULL)
    {
        perror("Impossibile aprire il testo da correggere");
        return 0;
    }

    char line[TEXT_BUFFER_SIZE];
    const char *delimiters = " \t\r\n,.;:!?\"'()[]{}";
    while (fgets(line, sizeof(line), text) != NULL)
    {
        char *word = strtok(line, delimiters);
        while (word != NULL)
        {
            normalize_ascii(word);
            if (!find_closest_words(dictionary, word, closest))
            {
                fprintf(stderr, "Impossibile trovare una correzione per '%s'.\n", word);
                fclose(text);
                return 0;
            }
            print_closest_words(word, closest);
            word = strtok(NULL, delimiters);
        }
    }

    if (ferror(text))
    {
        perror("Errore durante la lettura del testo");
        fclose(text);
        return 0;
    }

    fclose(text);
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Uso: %s <dictionary.txt> <correctme.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct Dictionary dictionary = {0};
    struct ClosestWords closest = {0};

    if (!dictionary_load(argv[1], &dictionary))
    {
        dictionary_free(&dictionary);
        return EXIT_FAILURE;
    }

    fprintf(stderr, "Parole caricate nel dizionario: %zu\n", dictionary.count);
    clock_t start = clock();
    int success = correct_text(argv[2], &dictionary, &closest);
    clock_t end = clock();
    fprintf(stderr, "Tempo di elaborazione: %.3f secondi\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(closest.items);
    dictionary_free(&dictionary);
    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
