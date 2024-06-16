#include "shared/comparable.h"
#include "shared/record.h"
#include "headers/merge_sort.h"

// Funzione per fondere due sottoarray ordinati
/* La funzione merge fonde due sottoarray ordinati in un singolo array ordinato.
Calcola le dimensioni dei due sottoarray: n1 per il sinistro e n2 per il destro.
Alloca memoria temporanea per i due sottoarray.
Copia i dati dai sottoarray originale a quelli temporanei.
Confronta gli elementi dei sottoarray temporanei e li copia nell'array principale in ordine.
Copia eventuali elementi rimanenti.
Libera la memoria temporanea. */
void merge(void *base, size_t l, size_t m, size_t r, size_t size, int (*compar)(const void *, const void *))
{
    size_t n1 = m - l + 1;
    size_t n2 = r - m;
    void *L = malloc(n1 * size);
    void *R = malloc(n2 * size);
    if (L == NULL || R == NULL)
    {
        perror("Errore durante l'allocazione di memoria temporanea");
        exit(EXIT_FAILURE);
    }
    memcpy(L, base + l * size, n1 * size);
    memcpy(R, base + (m + 1) * size, n2 * size);
    size_t i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (compar(L + i * size, R + j * size) <= 0)
        {
            memcpy(base + k * size, L + i * size, size);
            i++;
        }
        else
        {
            memcpy(base + k * size, R + j * size, size);
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        memcpy(base + k * size, L + i * size, size);
        i++;
        k++;
    }
    while (j < n2)
    {
        memcpy(base + k * size, R + j * size, size);
        j++;
        k++;
    }
    free(L);
    free(R);
}

// Funzione MergeSort ricorsiva
/* La funzione merge_sort è la parte ricorsiva del MergeSort. Essa:

Controlla se l'indice sinistro l è minore dell'indice destro r.
Calcola l'indice medio m.
Esegue ricorsivamente merge_sort sulla metà sinistra (l a m).
Esegue ricorsivamente merge_sort sulla metà destra (m + 1 a r).
Chiama la funzione merge per fondere i due sottoarray ordinati. */
void merge_sort(void *base, size_t l, size_t r, size_t size, int (*compar)(const void *, const void *))
{
    if (l < r)
    {
        size_t m = l + (r - l) / 2;
        merge_sort(base, l, m, size, compar);
        merge_sort(base, m + 1, r, size, compar);
        merge(base, l, m, r, size, compar);
    }
}

// Wrapper per la funzione di MergeSort ricorsiva
/* La funzione merge_sort_wrapper è un wrapper per la funzione di MergeSort ricorsiva. Essa:

Verifica che il puntatore base non sia nullo.
Chiama la funzione merge_sort con i parametri appropriati:
base: puntatore all'array da ordinare.
0: indice iniziale.
nitems - 1: indice finale.
size: dimensione di ciascun elemento.
compar: puntatore alla funzione di confronto. */
void merge_sort_wrapper(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))
{
    if (base != NULL)
        merge_sort(base, 0, nitems - 1, size, compar);
}
