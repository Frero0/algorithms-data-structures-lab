#include "edit_distance.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

// Funzione di utilità per calcolare la lunghezza di una stringa
size_t string_length(const char *s)
{
    return (s == NULL) ? 0 : strlen(s);
}

// Funzione di utilità per calcolare il minimo di due numeri
int min(int x, int y)
{
    return x < y ? x : y;
}

// Funzione di utilità per calcolare il minimo di tre numeri
int min1(int x, int y, int z)
{
    return min(min(x, y), z);
}

/* La funzione edit_distance calcola la distanza di editing tra due stringhe s1 e s2
di lunghezza m e n rispettivamente, utilizzando un approccio ricorsivo:
Se una delle due stringhe è vuota, ritorna la lunghezza dell'altra.
Calcola il costo delle tre operazioni possibili: sostituzione (d_no_op), cancellazione (d_canc), e inserimento (d_ins).
Restituisce il minimo tra questi tre costi. */
int edit_distance(char *s1, char *s2, int m, int n)
{
    // Se una delle due stringhe è vuota, ritorna la lunghezza dell'altra
    if (m == 0)
        return n;
    if (n == 0)
        return m;

    // Calcola i costi delle tre operazioni
    int d_no_op = (s1[0] == s2[0]) ? edit_distance(s1 + 1, s2 + 1, m - 1, n - 1) : INT_MAX;
    int d_canc = 1 + edit_distance(s1, s2 + 1, m, n - 1);
    int d_ins = 1 + edit_distance(s1 + 1, s2, m - 1, n);

    // Ritorna il minimo dei tre costi
    return min1(d_no_op, d_canc, d_ins);
}

/* edit_distance_rec è una funzione ausiliaria per calcolare la distanza di editing
tra due stringhe str1 e str2 usando la tecnica di memoization (memorizzazione dei risultati intermedi):
Utilizza una matrice memo per memorizzare i risultati parziali.
Se memo[i][j] è già calcolato, lo ritorna direttamente.
Se i o j sono zero, inizializza memo[i][j] rispettivamente con j o i.
Se i caratteri corrispondenti di str1 e str2 sono uguali, richiama ricorsivamente edit_distance_rec.
Altrimenti, calcola il costo delle operazioni di cancellazione e inserimento e sceglie il minimo. */
int edit_distance_rec(char *str1, char *str2, int i, int j, int **memo)
{
    if (memo[i][j] != -1)
        return memo[i][j];

    if (i == 0)
    {
        memo[i][j] = j;
    }
    else if (j == 0)
    {
        memo[i][j] = i;
    }
    else if (str1[i - 1] == str2[j - 1])
    {
        memo[i][j] = edit_distance_rec(str1, str2, i - 1, j - 1, memo);
    }
    else
    {
        memo[i][j] = 1 + min(edit_distance_rec(str1, str2, i, j - 1, memo),
                             edit_distance_rec(str1, str2, i - 1, j, memo));
    }

    return memo[i][j];
}

/* Descrizione: edit_distance_dyn calcola la distanza di editing tra due stringhe str1 e str2 utilizzando la memoization:
Se una delle stringhe è nulla, ritorna -1.
Alloca una matrice memo per memorizzare i risultati parziali delle chiamate ricorsive.
Calcola la distanza di editing chiamando edit_distance_rec con la matrice memo.
Libera la memoria allocata per memo dopo aver ottenuto il risultato. */
int edit_distance_dyn(char *str1, char *str2)
{
    if (str1 == NULL || str2 == NULL)
        return -1;

    int n = (int)strlen(str1);
    int m = (int)strlen(str2);

    // Crea la matrice di memorizzazione
    int **memo = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++)
    {
        memo[i] = (int *)malloc((m + 1) * sizeof(int));
        for (int j = 0; j <= m; j++)
        {
            memo[i][j] = -1;
        }
    }

    int result = edit_distance_rec(str1, str2, n, m, memo);

    // Libera la matrice di memorizzazione
    for (int i = 0; i <= n; i++)
    {
        free(memo[i]);
    }
    free(memo);

    return result;
}

/* Differenze tra l'Algoritmo Dinamico e quello Non Dinamico
Approccio Non Dinamico (edit_distance):

Utilizza una strategia ricorsiva semplice.
Calcola la distanza di editing per ogni coppia di sottostringhe ripetutamente.
Non memorizza i risultati intermedi, quindi è soggetto a un alto numero di chiamate ricorsive ridondanti,
 portando a prestazioni più lente, specialmente per input di grandi dimensioni.
Approccio Dinamico (edit_distance_dyn con edit_distance_rec e memoization):

Utilizza una memoization per memorizzare i risultati intermedi delle sottoproblematiche.
Evita di ricalcolare la distanza di editing per le stesse coppie di sottostringhe multiple volte.
Questo approccio riduce notevolmente il numero di chiamate ricorsive e migliora l'efficienza,
specialmente per input più grandi e complessi.
Conclusione
L'implementazione di edit_distance_dyn con memoization offre una soluzione più efficiente rispetto
all'implementazione non dinamica edit_distance. Utilizzando la memoization, si evitano i calcoli
ripetuti dei sottoproblemi, migliorando significativamente le prestazioni dell'algoritmo,
soprattutto per input di grandi dimensioni o con stringhe lunghe. */