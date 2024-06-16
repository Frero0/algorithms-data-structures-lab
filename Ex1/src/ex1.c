#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shared/comparable.h"
#include "headers/quick_sort.h"
#include "headers/merge_sort.h"
#include "shared/record.h"

int leggi_numero_identificatori(FILE *dati)
{
    int numero_identificatori = 0;
    int id;
    char parola[50] = ""; /* Assumo che la parola sia lunga al massimo 50 caratteri */
    /* Leggo ogni riga del file */
    while (fscanf(dati, "%d,", &id) != EOF)
    {
        /* Aumento il contatore per ogni riga letta */
        numero_identificatori++;
        /* Ignoro il resto della riga */
        fscanf(dati, "%*[^\n]");
        /* Ignoro il carattere newline */
        fgetc(dati);
    }
    /* Riporto l'indicatore del file all'inizio per usare il file nuovamente, se necessario */
    rewind(dati);
    return numero_identificatori;
}

void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo)
{
    /* arr è un puntatore a un array di strutture Record.
buffer è un array di caratteri usato per leggere le righe del file.
n_dati è il numero di record nel file di input, ottenuto chiamando leggi_numero_identificatori.
allocco arr dinamicamente per contenere n_dati record. Se l'allocazione fallisce, il programma termina. */
    struct Record *arr = NULL; // Inizializza a NULL
    char buffer[128];
    char *token;
    int i = 0;
    int n_dati = leggi_numero_identificatori(infile);
    printf("Ho contato %d di records all'interno di questo file!\n", n_dati);
    arr = malloc(n_dati * sizeof(struct Record));
    if (arr == NULL)
    {
        printf("Errore allocazione della memoria\n");
        exit(EXIT_FAILURE);
    }
    // Leggo e memorizzo ogni riga del file nel buffer e successivamente nei record
    /* Il ciclo for legge ogni riga del file di input usando fgets e la memorizza in buffer.
Ogni campo della struttura Record viene riempito con i valori letti dal buffer usando sscanf.
field1 viene allocato dinamicamente per contenere fino a 64 caratteri. */
    for (int i = 0; fgets(buffer, sizeof(buffer), infile) != NULL && i < n_dati; i++)
    {
        arr[i].field1 = malloc(64 * sizeof(char));
        if (arr[i].field1 == NULL)
        {
            printf("Error allocating memory\n");
            exit(EXIT_FAILURE);
        }
        if (sscanf(buffer, "%d,%63[^,],%d,%f", &arr[i].id, arr[i].field1, &arr[i].field2, &arr[i].field3) == -1)
            printf("Errore durante la lettura del file\n");
    }
    /* compar è un puntatore a funzione che punta alla funzione di 
    confronto appropriata basata sul campo specificato (1 per stringa, 2 per intero, 3 per float). */
    Compar compar =
        field == 1 ? compare_records_string : field == 2 ? compare_records_int
                                          : field == 3   ? compare_records_float
                                                         : NULL;
    /* In base al valore di algo, viene scelto e eseguito l'algoritmo di ordinamento (merge_sort o quick_sort). La macro TIMING 
    probabilmente misura il tempo di esecuzione dell'ordinamento.
fflush(stdout) viene usato per forzare la scrittura di tutti i buffer di output prima di misurare il tempo di esecuzione. */
    if (algo == 1)
    {
        fflush(stdout);
        TIMING(merge_sort_wrapper(arr, n_dati, sizeof(arr[0]), compar));
    }
    else if (algo == 2)
    {
        fflush(stdout);
        TIMING(quick_sort((void *)arr, n_dati, sizeof(arr[0]), compar));
    }
    else
    {
        printf("numero dell'algoritmo non valido\n");
        exit(EXIT_FAILURE);
    }
    /* I record ordinati vengono scritti nel file di output usando fprintf. */
    printf("Scrittura su file in corso..\n");
    for (int i = 0; i < n_dati; i++)
    {
        fprintf(outfile, "%d,%s,%d,%f\n", arr[i].id, arr[i].field1, arr[i].field2, arr[i].field3);
    }
    /* libero la memoria allocata dinamicamente per field1 di ogni record. */
    printf("Deallocazione in corso..\n");
    for (int j = 0; j < n_dati; j++)
    {
        free(arr[j].field1);
    }
    printf("Deallocazione effettuata :D \n");
}

int main(int argc, char const *argv[])
{
    /* Verifico che il numero di argomenti passati alla linea di comando sia 
    esattamente 4 (nome dell'eseguibile incluso). Se non lo è, stampo un messaggio di errore ed esco. */
    if (argc != 4)
    {
        printf("Quando lancio l'eseguibile devo avere: %s <input_file> <output_file> <field>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    /* Apro il file di input in modalità lettura ("r"). 
    Se il file non può essere aperto (ad esempio, se non esiste), stampo un messaggio di errore e termino. */
    FILE *nome = fopen(argv[1], "r");
    if (nome == NULL)
    {
        printf("Impossibile aprire il file di input\n");
        exit(EXIT_FAILURE);
    }
    /* Apro il file di output in modalità scrittura ("w"). 
    Se il file non può essere aperto (ad esempio, se i permessi non lo consentono), stampo un messaggio di errore e termino. */
    FILE *nome_out = fopen(argv[2], "w");
    if (nome_out == NULL)
    {
        printf("Impossibile aprire il file di output\n");
        exit(EXIT_FAILURE);
    }
    /* Converto il terzo argomento della linea di comando (una stringa) in un numero intero utilizzando atoi(). 
    Verifico poi che il numero sia compreso tra 1 e 3. Se non lo è, stampo un messaggio di errore e termino. */
    int field = atoi(argv[3]);
    if (field < 1 || field > 3)
    {
        printf("Campo non valido. Deve essere 1, 2 o 3.\n");
        exit(EXIT_FAILURE);
    }
    /* Chiedo all'utente di scegliere un algoritmo di ordinamento, merge_sort (1) o quick_sort (2). 
    Leggo la scelta tramite scanf() e verifico che sia 1 o 2. Se non lo è, stampo un messaggio di errore e termino. */
    int algo;
    printf("Inserisci 1 per merge_sort, 2 per quick_sort: ");
    scanf("%d", &algo);
    if (algo != 1 && algo != 2)
    {
        printf("Algoritmo non valido. Deve essere 1 o 2.\n");
        exit(EXIT_FAILURE);
    }
    sort_records(nome, nome_out, field, algo);
    /* Chiudo entrambi i file aperti per evitare perdite di memoria e garantire che tutti i dati siano scritti correttamente nel file di output. */
    fclose(nome);
    fclose(nome_out);
}
