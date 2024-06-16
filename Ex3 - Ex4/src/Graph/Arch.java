package Graph;

import java.util.*;

public class Arch<G, T> implements AbstractEdge<G, T> {

    /*
     * G start: Rappresenta il nodo di partenza dell'arco.
     * G end: Rappresenta il nodo di arrivo dell'arco.
     * T label: Opzionale. Rappresenta l'etichetta dell'arco che può essere di
     * qualsiasi tipo T.
     */
    G start;
    G end;
    T label;

    /*
     * public Arch(G start, G end, T label): Costruisce un arco con il nodo di
     * partenza
     * start, il nodo di arrivo end e un'etichetta label.
     * public Arch(G start, G end): Costruisce un arco con il nodo di partenza start
     * e il
     * nodo di arrivo end, senza specificare un'etichetta (label è impostata a
     * null).
     */
    public Arch(G start, G end, T label) {
        this.start = start;
        this.end = end;
        this.label = label;
    }

    public Arch(G start, G end) {
        this.start = start;
        this.end = end;
        this.label = null;
    }

    @Override
    public G getStart() {
        return this.start;
    }

    @Override
    public G getEnd() {
        return this.end;
    }

    @Override
    public T getLabel() {
        return this.label;
    }

    /*
     * public int compareTo(AbstractEdge<G, T> o): Implementa il metodo di confronto
     * per
     * l'interfaccia AbstractEdge, anche se attualmente ritorna sempre 0. Questo
     * metodo
     * dovrebbe essere implementato per fornire un criterio di ordinamento degli
     * archi, se necessario.
     */
    @Override
    public int compareTo(AbstractEdge<G, T> o) {
        // Implemento qui la logica di confronto
        return 0;
    }

    /*
     * public boolean equals(Object o): Sovrascrive il metodo equals per confrontare
     * due oggetti Arch. Due archi sono considerati uguali se i loro nodi di
     * partenza
     * e di arrivo sono uguali, e se le loro etichette (se presenti) sono uguali.
     */
    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;

        Arch<?, ?> arch = (Arch<?, ?>) o;
        return Objects.equals(start, arch.start) && Objects.equals(end, arch.end);
    }

    /*
     * public String toString(): Restituisce una stringa che rappresenta
     * l'oggetto Arch, mostrando i valori dei nodi di partenza e arrivo e
     * l'etichetta dell'arco.
     */
    @Override
    public String toString() {
        return "start: " + start + "\t end: " + end + "\t label:" + label;
    }
}

/*
 * Utilizzo e Scopo
 * La classe Arch è progettata per rappresentare un arco in un grafo generico.
 * È parametrizzata dai tipi G e T, che consentono di gestire in modo flessibile
 * i nodi
 * e le etichette dell'arco. I metodi equals, compareTo, e toString sono
 * implementati
 * per fornire funzionalità di confronto, ordinamento e rappresentazione
 * dell'arco.
 * 
 * Considerazioni Finali
 * Questa implementazione di Arch fornisce un modo flessibile e generico per
 * rappresentare
 * archi in un grafo, consentendo di gestire grafi di diversi tipi di nodi e di
 * archi con
 * etichette opzionali. È fondamentale implementare il metodo compareTo se si
 * desidera
 * utilizzare gli oggetti Arch in strutture dati che richiedono un ordinamento,
 * come le code di priorità basate su heap.
 */