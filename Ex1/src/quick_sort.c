#include "shared/comparable.h"
#include "headers/merge_sort.h"

// Funzione per scambiare due elementi dell'array
/* Crea un array temporaneo temp della stessa dimensione di un singolo elemento dell'array (size byte).
Copia il contenuto di a in temp.
Copia il contenuto di b in a.
Copia il contenuto di temp in b.
Questa funzione è essenziale per l'algoritmo di ordinamento poiché consente di scambiare gli elementi quando
necessario durante l'ordinamento, senza preoccuparsi del tipo di dati specifico dell'array grazie
all'utilizzo di memcpy per operare su blocchi di memoria di dimensione size. */
void swap(void *a, void *b, size_t size)
{
    char temp[size];

    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

//
// Funzione per dividere l'array e restituire l'indice del pivot
/* La funzione partition divide l'array in due parti e restituisce l'indice del pivot. Ecco un breve riassunto del suo funzionamento:

Seleziona il pivot come l'elemento centrale dell'array.
Copia il valore del pivot in pivot_value.
Inizializza due indici: i all'inizio e j alla fine dell'array.
Itera attraverso l'array:
Incrementa i finché l'elemento puntato è minore del pivot.
Decrementa j finché l'elemento puntato è maggiore del pivot.
Se i è maggiore o uguale a j, restituisce j come l'indice del pivot.
Scambia gli elementi ai puntatori i e j.
Se l'elemento a i è uguale al pivot, incrementa i.
Se l'elemento a j è uguale al pivot, decrementa j.
Questo processo divide l'array in elementi minori del pivot e maggiori del pivot, posizionando il pivot alla sua posizione corretta.*/
size_t partition(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))
{
    void *pivot = (char *)base + (((nitems - 1) / 2) * size);

    char pivot_value[size];
    memcpy(pivot_value, pivot, size);

    size_t i = 0;
    size_t j = nitems - 1;

    while (1)
    {
        while (compar((char *)base + i * size, pivot_value) < 0)
            i++;
        while (compar((char *)base + j * size, pivot_value) > 0)
            j--;

        if (i >= j)
            return j;
        swap((char *)base + i * size, (char *)base + j * size, size);
        if (compar((char *)base + i * size, pivot_value) == 0)
            i++;
        if (compar((char *)base + j * size, pivot_value) == 0)
            j--;
    }
}

// Funzione QuickSort ricorsiva
/* La funzione quick_sort è una versione ricorsiva del QuickSort. Ecco un breve riassunto del suo funzionamento:

Verifica se l'array è non nullo.
Se l'array ha un elemento o meno, termina la ricorsione (base case).
Altrimenti, calcola l'indice del pivot tramite la funzione partition.
Ricorsivamente applica quick_sort alla parte sinistra del pivot.
Ricorsivamente applica quick_sort alla parte destra del pivot.
Il processo di partizionamento e la ricorsione assicurano che l'array venga ordinato correttamente. */
void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))
{
    if (base != NULL)
    {
        if (nitems <= 1)
        {
            return;
        }
        size_t pivot_index = partition(base, nitems, size, compar);
        quick_sort(base, pivot_index + 1, size, compar);
        quick_sort((char *)base + (pivot_index + 1) * size, nitems - pivot_index - 1, size, compar);
    }
}
