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
    char parola[50] = ""; /* Assumiamo che la parola sia lunga al massimo 50 caratteri */
    /* Leggiamo ogni riga del file */
    while (fscanf(dati, "%d,", &id) != EOF)
    {
        /* Aumentiamo il contatore per ogni riga letta */
        numero_identificatori++;
        /* Ignoriamo il resto della riga */
        fscanf(dati, "%*[^\n]");
        /* Ignoriamo il carattere newline */
        fgetc(dati);
    }
    /* Riportiamo l'indicatore del file all'inizio per usare il file nuovamente, se necessario */
    rewind(dati);
    return numero_identificatori;
}

int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        printf("Quando lancio l'eseguibile devo avere: %s <input_file> <output_file> <field>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *nome = fopen(argv[1], "r");
    if (nome == NULL)
    {
        printf("Impossibile aprire il file di input\n");
        exit(EXIT_FAILURE);
    }
    FILE *nome_out = fopen(argv[2], "w");
    if (nome_out == NULL)
    {
        printf("Impossibile aprire il file di output\n");
        exit(EXIT_FAILURE);
    }
    int field = atoi(argv[3]);
    if (field < 1 || field > 3)
    {
        printf("Campo non valido. Deve essere 1, 2 o 3.\n");
        exit(EXIT_FAILURE);
    }
    int algo;
    printf("Inserisci 1 per merge_sort, 2 per quick_sort: ");
    scanf("%d", &algo);
    if (algo != 1 && algo != 2)
    {
        printf("Algoritmo non valido. Deve essere 1 o 2.\n");
        exit(EXIT_FAILURE);
    }
    sort_records(nome, nome_out, field, algo);
    fclose(nome);
    fclose(nome_out);
}
