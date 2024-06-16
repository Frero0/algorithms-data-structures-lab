#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#include "edit_distance.h"

int main(int argc, char **argv)
{
    /*Prima di tutto, apro il file correctme.txt per leggere la frase da correggere
    e dictionary.txt per accedere al dizionario delle parole. */
    // Checking open file stream
    FILE *correctme = fopen("/Users/federicosantorsola/Library/Mobile Documents/com~apple~CloudDocs/Desktop/Università 🧑🏻‍🎓🏫🧿/2 Anno/ALGORITMI E STRUTTURE DATI/LAB/Progetto/Ex2/correctme.txt", "r+");
    if (correctme == NULL)
    {
        printf("Err: Cannot open correctme.txt FILE\n");
        exit(EXIT_FAILURE);
    }

    FILE *dictionary = fopen("/Users/federicosantorsola/Library/Mobile Documents/com~apple~CloudDocs/Desktop/Università 🧑🏻‍🎓🏫🧿/2 Anno/ALGORITMI E STRUTTURE DATI/LAB/Progetto/Ex2/dictionary.txt", "r+");
    if (dictionary == NULL)
    {
        printf("Err: Cannot open dictionary.txt FILE\n");
        exit(EXIT_FAILURE);
    }
    /* Dichiaro varie variabili utilizzate nel programma, tra cui act per contenere la distanza
    di editing corrente, min_edit per tener traccia della minima distanza di editing trovata, e
    vari array di caratteri per contenere le parole e la frase in input. */
    // Vars
    int act;
    int min_edit = INT_MAX;
    char *tok;
    char word[1024];
    char choosen[1024];
    char input[1024];

    // Reading the sentence that needs to be corrected
    fscanf(correctme, "%[^\n]", input);
    /* Tokenizzo la frase in input utilizzando spazi, virgole, punti e tabulazioni come separatori.
    strtok mi permette di estrarre ogni parola una alla volta da input. */
    // Tokenizing the sentence and find out the Edit-distance
    tok = strtok(input, ",.\t ");
    /* Chiedo all'utente se vuole utilizzare l'algoritmo dinamico per calcolare la distanza di editing.
    Leggo la sua risposta usando fgets, poi rimuovo il newline alla fine (se presente) con strcspn.
    Se l'utente digita "si", use_dynamic diventa true. */
    // Chiedi all'utente quale algoritmo utilizzare
    char user_choice[10];
    printf("Vuoi utilizzare l'algoritmo dinamico? (si/no): ");
    fgets(user_choice, 10, stdin);
    user_choice[strcspn(user_choice, "\n")] = 0; // Rimuove il newline alla fine, se presente

    bool use_dynamic = (strcmp(user_choice, "si") == 0);

    clock_t start, end;
    double cpu_time_used;

    start = clock(); // Inizia il timer prima del ciclo
    /* Per ogni parola tok estratta dalla frase:
Converto il primo carattere in minuscolo usando tolower.
Leggo ogni parola dal file dictionary.txt e calcolo la distanza di editing tra tok e word usando
l'algoritmo dinamico (edit_distance_dyn) o l'algoritmo standard (edit_distance), a seconda della scelta dell'utente.
Aggiorno min_edit e choosen se trovo una parola nel dizionario con una distanza di editing inferiore a quella corrente.
Stampiamo il risultato con printf.
Resetto min_edit e reimposto la posizione del cursore all'inizio di dictionary.txt con fseek per la prossima iterazione. */
    while (tok != NULL)
    {
        tok[0] = (char)tolower(tok[0]);
        while (fscanf(dictionary, "%[^\n]", word) != EOF)
        {
            fgetc(dictionary);
            if (use_dynamic)
            {
                act = edit_distance_dyn(tok, word);
            }
            else
            {
                act = edit_distance(tok, word, strlen(tok), strlen(word));
            }
            if (act < min_edit)
            {
                min_edit = act;
                strcpy(choosen, word);
            }
        }
        printf("Word: %s, minimum edit-distance: %d, correct world: %s\n", tok, min_edit, choosen);
        tok = strtok(NULL, ",.\t ");
        min_edit = INT_MAX;
        fseek(dictionary, 0, SEEK_SET);
    }

    /* Misuro il tempo totale di esecuzione del ciclo utilizzando clock(), calcolo la differenza tra end e start,
    e converto il risultato in secondi. Stampo il tempo totale di esecuzione con printf. */
    end = clock(); // Ferma il timer dopo il ciclo
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo di esecuzione totale: %f secondi\n", cpu_time_used); // Stampa il tempo totale di esecuzione

    // Chiudo i file correctme.txt e dictionary.txt per liberare le risorse.
    fclose(correctme);
    fclose(dictionary);

    return 0;
}