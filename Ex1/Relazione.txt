----- Relazione di laboratorio ASD 2023/2024 ----- di Santorsola Federico

Come richiesto, la relazione è stata affrontata sul esercizio 1.

/////////////// ANALISI ESERCIZIO 1 ///////////////


 L'ordinamento rapido (Quick Sort) e l'ordinamento per fusione (Merge Sort) sono entrambi algoritmi 
 di ordinamento efficienti con complessità temporale O(n log n), ma ho notato alcune differenze chiave:

1 - Metodo di ordinamento: 
Quick Sort è un algoritmo di ordinamento in loco che utilizza la tecnica 
“divide et impera”. Sceglie un elemento come pivot e partiziona l’array attorno al pivot. 
Questo significa che gli elementi minori del pivot vengono spostati prima del pivot e gli 
elementi maggiori vengono spostati dopo. Questo processo viene ripetuto per ogni partizione 
fino a quando l’intero array non è ordinato. D’altra parte, Merge Sort divide l’array in due metà,
le ordina separatamente e poi le fonde. Questo processo viene ripetuto fino a quando non rimane un 
solo elemento in ogni partizione, il che significa che l’array è ordinato.

Le conseguenze di tutto ciò, sono le seguenti:

Per quanto riguarda il Quick Sort:

Efficienza spaziale: 
Poiché Quick Sort è un algoritmo di ordinamento in loco, 
utilizza meno memoria rispetto a Merge Sort. Questo lo rende più efficiente dal 
punto di vista dello spazio, specialmente quando si lavora con grandi set di dati.

Scelta del pivot: 
La scelta del pivot in Quick Sort può avere un impatto significativo sulle sue prestazioni. 
Se il pivot è scelto in modo non ottimale, l’algoritmo può degradare a un tempo di esecuzione quadratico, cioè O(n^2).

Ordinamento instabile:
Quick Sort non è un algoritmo di ordinamento stabile, il che significa che l’ordine relativo 
degli elementi uguali può cambiare durante l’ordinamento. Questo può essere un problema in alcune applicazioni.

Per quanto riguarda il Merge Sort:

Uso della memoria: 
Merge Sort richiede spazio di memoria aggiuntivo proporzionale alla dimensione dell’array da ordinare. 
Questo può essere un problema quando si lavora con grandi set di dati.

Ordinamento stabile: 
A differenza di Quick Sort, Merge Sort è un algoritmo di ordinamento 
stabile, il che significa che mantiene l’ordine relativo degli elementi uguali. Questo può 
essere importante in alcune applicazioni, come quando si ordinano record con chiavi multiple.

Prestazioni costanti: 
Merge Sort ha un tempo di esecuzione costante di O(n log n), 
indipendentemente dalla scelta dei dati. Questo lo rende una scelta affidabile quando 
l’efficienza temporale è una preoccupazione.

2 - Uso della memoria: 
Quick Sort è un algoritmo in loco, il che significa che non richiede memoria 
aggiuntiva significativa. Tuttavia, nel caso peggiore, può richiedere spazio di memoria O(n) per 
la pila di chiamate ricorsive. Merge Sort, d’altra parte, non è un algoritmo in loco e richiede 
spazio di memoria temporaneo proporzionale alla dimensione dell’array da ordinare. Questo può 
essere un problema per array molto grandi.

3 - Stabilità: 
Merge Sort è stabile, il che significa che mantiene l’ordine relativo degli elementi 
uguali. Questo può essere importante in alcune applicazioni, come quando si ordinano record con 
chiavi multiple. Quick Sort non è stabile, il che significa che l’ordine relativo degli elementi 
uguali può cambiare durante l’ordinamento.

4 - Performance: 
In media, entrambi gli algoritmi hanno un tempo di esecuzione O(n log n). Tuttavia, 
nel caso peggiore, Quick Sort può degradare a O(n^2) se il pivot scelto è il più piccolo o il più 
grande elemento. Questo può essere mitigato utilizzando una strategia di selezione del pivot più 
sofisticata, come il pivot mediano di tre. Merge Sort mantiene sempre un tempo di esecuzione 
O(n log n), indipendentemente dalla scelta dei dati.

5 - Applicabilità: 
Merge Sort funziona meglio per strutture di dati che non possono essere accessibili 
in modo casuale, come le liste collegate, poiché può fondere liste in tempo O(n). Quick Sort 
funziona meglio per gli array e le strutture di dati che possono essere accessibili in modo casuale,
poiché può partizionare un array in tempo O(n).


----------------- SCELTE IMPLEMENTATIVE -----------------

Per quanto riguarda sort_records:

Allocazione di memoria: Utilizza malloc per allocare dinamicamente memoria per una 
struttura Record in base al numero di record nel file.
Lettura dei dati: Legge e memorizza ogni riga del file di input in una struttura Record.
Scelta dell'algoritmo di ordinamento: A seconda dell'input dell'utente, chiama merge_sort_wrapper o quick_sort per ordinare i record.
Scrittura su file: Scrive i record ordinati nel file di output.
Deallocazione della memoria: Libera la memoria allocata per ogni record alla fine dell'esecuzione.

Per quanto riguarda merge_sort_wrapper:

Esegue il wrapper per la funzione merge_sort, verificando prima che il puntatore base non sia nullo.
merge_sort:

Implementa l'algoritmo MergeSort ricorsivo, diviso in due funzioni:
merge_sort: Ricorsivamente suddivide l'array in sottoarray, poi li fonde ordinati usando la funzione merge.
merge: Fonde due sottoarray ordinati in un array ordinato.
Utilizzo di memoria temporanea: Utilizza malloc per creare array temporanei durante la fase di merge.
quick_sort:

Implementa l'algoritmo QuickSort ricorsivo.
Partizione: Utilizza la funzione partition per dividere l'array in base a un pivot e restituire l'indice del pivot.
partition:

Trova un pivot nel mezzo dell'array, quindi sposta gli elementi minori del pivot a sinistra e quelli maggiori a destra.
Utilizza memcpy per copiare i dati degli elementi durante lo scambio.
swap:

Utilizza memcpy per scambiare i dati tra due elementi di un array di dimensione generica,
utilizzando un array temporaneo di dimensione size.
Queste funzioni mostrano scelte cruciali come l'allocazione dinamica della memoria, 
la gestione dei dati strutturati, l'implementazione di algoritmi di ordinamento efficienti 
come MergeSort e QuickSort, e l'uso di operazioni basate su memoria per mantenere la generalità e la flessibilità dell'implementazione.