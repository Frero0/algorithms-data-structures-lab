package Graph;

import java.util.*;

public class Graph<G, T> implements AbstractGraph<G, T> {

    /*
     * private boolean directed: Indica se il grafo è diretto (true) o non diretto
     * (false).
     * private boolean labelled: Indica se il grafo è etichettato (true) o non
     * etichettato (false).
     * private Map<G, Set<Arch<G, T>>> graph: Struttura dati che rappresenta il
     * grafo usando una
     * mappa di nodi G a insiemi di archi Arch<G, T> associati a ciascun nodo.
     */
    private boolean directed;
    private boolean labelled;
    private Map<G, Set<Arch<G, T>>> graph;

    /*
     * public Graph(boolean directed, boolean labelled): Costruisce un nuovo grafo
     * inizializzando
     * le variabili directed e labelled e creando una nuova istanza di HashMap per
     * rappresentare il grafo.
     */
    public Graph(boolean directed, boolean labelled) {
        this.directed = directed;
        this.labelled = labelled;
        this.graph = new HashMap<>();
    }

    public boolean isDirected() {
        return this.directed;
    }

    public boolean isLabelled() {
        return this.labelled;
    }

    public boolean addNode(G a) {
        if (this.graph.containsKey(a)) {
            return false;
        }
        this.graph.put(a, new HashSet<>());
        return true;
    }

    public boolean addEdge(G a, G b, T l) {
        if (!this.graph.containsKey(a) || !this.graph.containsKey(b)) {
            return false;
        }
        Arch<G, T> edge = new Arch<>(a, b, l);
        this.graph.get(a).add(edge);
        if (!this.directed) {
            Arch<G, T> reverseEdge = new Arch<>(b, a, l);
            this.graph.get(b).add(reverseEdge);
        }
        return true;
    }

    public boolean containsNode(G a) {
        return this.graph.containsKey(a);
    }

    public boolean containsEdge(G a, G b) {
        if (!this.graph.containsKey(a)) {
            return false;
        }
        for (Arch<G, T> edge : this.graph.get(a)) {
            if (edge.getEnd().equals(b)) {
                return true;
            }
        }
        return false;
    }

    public boolean removeNode(G a) {
        if (!this.graph.containsKey(a)) {
            return false;
        }
        this.graph.remove(a);
        for (Set<Arch<G, T>> edges : this.graph.values()) {
            edges.removeIf(edge -> edge.getStart().equals(a) || edge.getEnd().equals(a));
        }
        return true;
    }

    public boolean removeEdge(G a, G b) {
        if (!this.graph.containsKey(a)) {
            return false;
        }
        Set<Arch<G, T>> edges = this.graph.get(a);
        Arch<G, T> edgeToRemove = null;
        for (Arch<G, T> edge : edges) {
            if (edge.getEnd().equals(b)) {
                edgeToRemove = edge;
                break;
            }
        }
        if (edgeToRemove == null) {
            return false;
        }
        edges.remove(edgeToRemove);
        if (!this.directed) {
            Set<Arch<G, T>> reverseEdges = this.graph.get(b);
            Arch<G, T> reverseEdgeToRemove = null;
            for (Arch<G, T> edge : reverseEdges) {
                if (edge.getEnd().equals(a)) {
                    reverseEdgeToRemove = edge;
                    break;
                }
            }
            if (reverseEdgeToRemove != null) {
                reverseEdges.remove(reverseEdgeToRemove);
            }
        }
        return true;
    }

    public int numNodes() {
        return this.graph.size();
    }

    public int numEdges() {
        int count = 0;
        for (Set<Arch<G, T>> edges : this.graph.values()) {
            count += edges.size();
        }
        return this.directed ? count : count / 2;
    }

    // public Collection<G> getNodes(): Restituisce una collezione contenente tutti
    // i nodi presenti nel grafo.
    public Collection<G> getNodes() {
        return new ArrayList<>(this.graph.keySet());
    }

    // public Collection<? extends AbstractEdge<G, T>> getEdges(): Restituisce una
    // collezione contenente tutti gli archi presenti nel grafo.
    public Collection<? extends AbstractEdge<G, T>> getEdges() {
        List<AbstractEdge<G, T>> allEdges = new ArrayList<>();
        for (Set<Arch<G, T>> edges : this.graph.values()) {
            allEdges.addAll(edges);
        }
        return allEdges;
    }

    // public Collection<? extends AbstractEdge<G, T>> getEdgesFrom(G node):
    // Restituisce una collezione di archi che partono dal nodo specificato node.
    public Collection<? extends AbstractEdge<G, T>> getEdgesFrom(G node) {
        if (!this.graph.containsKey(node)) {
            throw new IllegalArgumentException("Node does not exist in the graph");
        }
        return new ArrayList<>(this.graph.get(node));
    }

    // public Collection<G> getNeighbours(G a): Restituisce una collezione di nodi
    // adiacenti al nodo a.
    public Collection<G> getNeighbours(G a) {
        Set<G> neighbours = new HashSet<>();
        if (this.graph.containsKey(a)) {
            for (Arch<G, T> edge : this.graph.get(a)) {
                neighbours.add(edge.getEnd());
            }
        }
        return neighbours;
    }

    public T getLabel(G a, G b) {
        if (graph.containsKey(a)) {
            Set<Arch<G, T>> edges = graph.get(a);
            for (Arch<G, T> edge : edges) {
                if (edge.getEnd().equals(b)) {
                    return edge.getLabel();
                }
            }
        }
        return null;
    }
}

/*
 * Utilizzo e Scopo
 * La classe Graph fornisce un'implementazione generica di un grafo che supporta
 * operazioni di
 * aggiunta, rimozione e consultazione di nodi e archi. È progettata per essere
 * estensibile tramite
 * l'implementazione delle interfacce AbstractGraph<G, T> e AbstractEdge<G, T>,
 * consentendo così la
 * gestione di grafi diretti o non diretti, etichettati o non etichettati, con
 * qualsiasi tipo di nodo
 * e di etichetta per gli archi.
 * 
 * Considerazioni Finali
 * Questa implementazione di Graph è adatta per una vasta gamma di applicazioni
 * che richiedono la
 * modellazione di relazioni tra entità mediante grafi. È flessibile e può
 * essere adattata alle
 * specifiche esigenze dell'applicazione utilizzando i parametri generici G e T
 * e i metodi forniti
 * per manipolare e interrogare il grafo.
 */