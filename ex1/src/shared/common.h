#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "comparable.h"

#define RAND(min, max) ((rand() % (max - min + 1)) + min)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define BZERO(x, x_size) memset(x, 0, x_size)
#define TIMING(a)                                                       \
  do                                                                    \
  {                                                                     \
    clock_t start = clock();                                            \
    a;                                                                  \
    clock_t end = clock();                                              \
    printf("%s: %f sec\n", #a, (double)(end - start) / CLOCKS_PER_SEC); \
  } while (0)

/*
Questa macro definisce una scorciatoia per l'uso della funzione scanf().
La macro viene definita con il nome ISCANF, che accetta due argomenti, denotati da a e b. */
#define ISCANF(a, b)                                                                   \
  /*                                                                                   \
  Questa è una tecnica comune usata nelle macro per garantire                         \
  che la macro si comporti correttamente in presenza di blocchi                        \
  di codice, come ad esempio con un if o un else. Il blocco do {...}                   \
  while (0) forza l'espansione della macro come se fosse una singola                   \
  istruzione, evitando così problemi con la grammatica del linguaggio. */             \
  do                                                                                   \
  {                                                                                    \
    /*                                                                                 \
    All'interno del blocco do {...} while (0), viene dichiarata una variabile          \
    ignored di tipo int, ma non viene mai utilizzata nel codice successivo.            \
     Questo serve a evitare eventuali warning del compilatore riguardo a variabili     \
     non utilizzate. L'attributo __attribute__((unused)) viene utilizzato per indicare \
     al compilatore che la variabile è intenzionalmente non utilizzata. */            \
    int ignored __attribute__((unused));                                               \
    /*                                                                                 \
    All'interno del blocco do {...} while (0), viene chiamata la funzione scanf(a, b), \
     dove a e b sono gli argomenti passati alla macro. La scanf()                      \
      legge l'input da stdin (standard input) secondo il formato specificato           \
      da a e lo memorizza nella variabile specificata da b. */                         \
    ignored = scanf(a, b);                                                             \
  } while (0)

enum Type
{
  TYPE_INT,
  TYPE_DOUBLE,
  TYPE_STRING,
  TYPE_CHAR,
  TYPE_LONG,
  TYPE_FLOAT,
  TYPE_POINTER,
  TYPE_RECORD
};