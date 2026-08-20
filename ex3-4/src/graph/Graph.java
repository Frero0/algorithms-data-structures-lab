package graph;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * Sparse graph implementation backed by adjacency sets.
 */
public class Graph<V, L> implements AbstractGraph<V, L> {
    private final boolean directed;
    private final boolean labelled;
    private final Map<V, Set<Arch<V, L>>> adjacency;
    private int edgeCount;

    public Graph(boolean directed, boolean labelled) {
        this.directed = directed;
        this.labelled = labelled;
        this.adjacency = new HashMap<>();
    }

    @Override
    public boolean isDirected() {
        return directed;
    }

    @Override
    public boolean isLabelled() {
        return labelled;
    }

    @Override
    public boolean addNode(V node) {
        if (node == null || adjacency.containsKey(node)) {
            return false;
        }
        adjacency.put(node, new HashSet<>());
        return true;
    }

    @Override
    public boolean addEdge(V start, V end, L label) {
        if (start == null || end == null
                || !adjacency.containsKey(start)
                || !adjacency.containsKey(end)
                || (labelled && label == null)) {
            return false;
        }

        L storedLabel = labelled ? label : null;
        Arch<V, L> edge = new Arch<>(start, end, storedLabel);
        if (!adjacency.get(start).add(edge)) {
            return false;
        }

        if (!directed && !start.equals(end)) {
            adjacency.get(end).add(new Arch<>(end, start, storedLabel));
        }
        edgeCount++;
        return true;
    }

    @Override
    public boolean containsNode(V node) {
        return node != null && adjacency.containsKey(node);
    }

    @Override
    public boolean containsEdge(V start, V end) {
        return findEdge(start, end) != null;
    }

    @Override
    public boolean removeNode(V node) {
        if (!containsNode(node)) {
            return false;
        }

        List<Arch<V, L>> outgoing = new ArrayList<>(adjacency.get(node));
        for (Arch<V, L> edge : outgoing) {
            removeEdge(node, edge.getEnd());
        }

        if (directed) {
            List<V> sources = new ArrayList<>(adjacency.keySet());
            for (V source : sources) {
                if (!source.equals(node) && containsEdge(source, node)) {
                    removeEdge(source, node);
                }
            }
        }

        adjacency.remove(node);
        return true;
    }

    @Override
    public boolean removeEdge(V start, V end) {
        Arch<V, L> edge = findEdge(start, end);
        if (edge == null) {
            return false;
        }

        adjacency.get(start).remove(edge);
        if (!directed && !start.equals(end)) {
            Arch<V, L> reverse = findEdge(end, start);
            if (reverse != null) {
                adjacency.get(end).remove(reverse);
            }
        }
        edgeCount--;
        return true;
    }

    @Override
    public int numNodes() {
        return adjacency.size();
    }

    @Override
    public int numEdges() {
        return edgeCount;
    }

    @Override
    public Collection<V> getNodes() {
        return new ArrayList<>(adjacency.keySet());
    }

    @Override
    public Collection<? extends AbstractEdge<V, L>> getEdges() {
        List<AbstractEdge<V, L>> edges = new ArrayList<>();
        for (Set<Arch<V, L>> adjacentEdges : adjacency.values()) {
            edges.addAll(adjacentEdges);
        }
        return edges;
    }

    public Collection<? extends AbstractEdge<V, L>> getEdgesFrom(V node) {
        if (!containsNode(node)) {
            throw new IllegalArgumentException("The node does not exist in the graph");
        }
        return new ArrayList<>(adjacency.get(node));
    }

    @Override
    public Collection<V> getNeighbours(V node) {
        Set<V> neighbours = new HashSet<>();
        if (!containsNode(node)) {
            return neighbours;
        }
        for (Arch<V, L> edge : adjacency.get(node)) {
            neighbours.add(edge.getEnd());
        }
        return neighbours;
    }

    @Override
    public L getLabel(V start, V end) {
        Arch<V, L> edge = findEdge(start, end);
        return edge == null ? null : edge.getLabel();
    }

    private Arch<V, L> findEdge(V start, V end) {
        if (start == null || end == null || !adjacency.containsKey(start)) {
            return null;
        }
        for (Arch<V, L> edge : adjacency.get(start)) {
            if (edge.getEnd().equals(end)) {
                return edge;
            }
        }
        return null;
    }
}
