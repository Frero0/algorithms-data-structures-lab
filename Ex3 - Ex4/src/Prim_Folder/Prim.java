package Prim_Folder;

import priorityqueue.*;
import Graph.*;

import java.util.*;
import java.io.*;

public class Prim {

    /*
     * public static <V, L extends Number & Comparable<L>> Collection<? extends
     * AbstractEdge<V, L>>
     * minimumSpanningForest(Graph<V, L> graph): Questo metodo calcola la minima
     * foresta ricoprente utilizzando
     * l'algoritmo di Prim. Prende in input un grafo graph parametrizzato con nodi
     * di tipo V e archi etichettati
     * di tipo L extends Number & Comparable<L>.
     */
    public static <V, L extends Number & Comparable<L>> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(
            Graph<V, L> graph) {

        /*
         * Set<V> visited: Set utilizzato per tenere traccia dei nodi visitati durante
         * la costruzione della MST.
         */

        Set<V> visited = new HashSet<>();
        /*
         * priorityqueue.PriorityQueue<AbstractEdge<V, L>> queue: Coda di priorità
         * utilizzata per
         * gestire gli archi in ordine crescente in base al valore dell'etichetta.
         */
        priorityqueue.PriorityQueue<AbstractEdge<V, L>> queue = new priorityqueue.PriorityQueue<>(
                Comparator.comparing(AbstractEdge::getLabel));
        /* List<AbstractEdge<V, L>> result: Lista che conterrà gli archi della MST. */
        List<AbstractEdge<V, L>> result = new ArrayList<>();

        /*
         * Il metodo procede iterando su tutti i nodi del grafo non ancora visitati,
         * aggiungendo gli archi
         * incidenti dei nodi visitati alla coda queue. Poi, finché la coda non è vuota,
         * estrae l'arco con
         * il valore di etichetta minimo e aggiunge il nodo finale dell'arco non
         * visitato alla MST se non
         * già visitato. Questo processo continua finché tutti i nodi raggiungibili sono
         * inclusi nella MST.
         */
        for (V node : graph.getNodes()) {
            if (!visited.contains(node)) {
                visited.add(node);
                queue.addAll(graph.getEdgesFrom(node));

                while (!queue.empty()) {
                    AbstractEdge<V, L> edge = queue.top();
                    queue.pop();
                    V nextNode = visited.contains(edge.getStart()) ? edge.getEnd() : edge.getStart();

                    if (!visited.contains(nextNode)) {
                        visited.add(nextNode);
                        result.add(edge);
                        queue.addAll(graph.getEdgesFrom(nextNode));
                    }
                }
            }
        }

        return result;
    }

    public static void main(String[] args) throws IOException {
        // leggi i dati CSV del grafo dal percorso in args[1]
        Graph<String, Float> graph = new Graph<>(false, true);
        try (BufferedReader reader = new BufferedReader(new FileReader(args[0]))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                String place1 = parts[0];
                String place2 = parts[1];
                Float distance = Float.parseFloat(parts[2]);
                graph.addNode(place1);
                graph.addNode(place2);
                graph.addEdge(place1, place2, distance);
            }
        }

        // calcola la minima foresta ricoprente con minimumSpanningForest
        Collection<? extends AbstractEdge<String, Float>> mst = minimumSpanningForest(graph);

        // scrivi su standard output solo la descrizione della foresta calcolata come
        // CSV con formato analogo a quello in input
        for (AbstractEdge<String, Float> edge : mst) {
            System.out.println(edge.getStart() + "," + edge.getEnd() + "," + edge.getLabel());
        }

        // su standard error si possono scrivere ulteriori informazioni, come il numero
        // di nodi e archi nella foresta calcolata,
        // o il peso totale della foresta
        int numberOfNodes = graph.getNodes().size();
        int numberOfEdges = mst.size(); // MST avrà sempre n-1 archi per un grafo connesso
        System.err.println("Number of nodes in the MST: " + numberOfNodes);
        System.err.println("Number of edges in the MST: " + numberOfEdges);
        System.err.println("Total weight of the MST: " + mst.stream().mapToDouble(AbstractEdge::getLabel).sum());
    }
}

/*
 * javac ../priorityqueue/PriorityQueueException.java
 * ../priorityqueue/AbstractQueue.java ../priorityqueue/PriorityQueue.java
 * ../Graph/AbstractGraph.java ../Graph/AbstractEdge.java ../Graph/Arch.java
 * ../Graph/Graph.java Prim.java -d ../../bld/
 */
/* java Prim_Folder/Prim ../src/Prim_Folder/italian_dist_graph\ 2.csv */

/*
 * Utilizzo e Scopo
 * La classe Prim è progettata per essere eseguita da riga di comando, leggere
 * un file CSV che
 * rappresenta un grafo pesato non diretto, calcolare la MST utilizzando
 * l'algoritmo di Prim e stampare
 * i risultati. È adatta per applicazioni che richiedono la costruzione di MST
 * per reti di collegamenti,
 * strade, reti di comunicazione, etc.
 * 
 * Considerazioni Finali
 * La classe Prim dimostra l'utilizzo pratico degli algoritmi di MST su grafi
 * pesati.
 * È implementata in modo efficiente utilizzando una coda di priorità per
 * gestire gli archi in
 * ordine crescente di peso, assicurando così la costruzione rapida della MST.
 * La sua modularità
 * permette di essere adattata facilmente ad altri tipi di grafi e tipologie di
 * input, mantenendo
 * comunque una chiara logica di calcolo e output dei risultati.
 */