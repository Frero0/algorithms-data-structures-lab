package prim;

import static org.junit.Assert.assertEquals;

import graph.AbstractEdge;
import graph.Graph;

import java.util.Collection;

import org.junit.Test;

public class PrimTests {
    @Test
    public void connectedGraphProducesMinimumSpanningTree() {
        Graph<String, Float> graph = new Graph<>(false, true);
        addEdge(graph, "A", "B", 1.0f);
        addEdge(graph, "A", "C", 5.0f);
        addEdge(graph, "B", "C", 2.0f);
        addEdge(graph, "C", "D", 1.5f);
        addEdge(graph, "B", "D", 8.0f);

        Collection<? extends AbstractEdge<String, Float>> forest =
                Prim.minimumSpanningForest(graph);

        assertEquals(3, forest.size());
        assertEquals(4.5, totalWeight(forest), 0.0001);
    }

    @Test
    public void disconnectedGraphProducesMinimumSpanningForest() {
        Graph<String, Float> graph = new Graph<>(false, true);
        addEdge(graph, "A", "B", 1.0f);
        addEdge(graph, "B", "C", 2.0f);
        addEdge(graph, "D", "E", 4.0f);
        graph.addNode("F");

        Collection<? extends AbstractEdge<String, Float>> forest =
                Prim.minimumSpanningForest(graph);

        assertEquals(3, forest.size());
        assertEquals(7.0, totalWeight(forest), 0.0001);
    }

    @Test(expected = IllegalArgumentException.class)
    public void directedGraphIsRejected() {
        Prim.minimumSpanningForest(new Graph<String, Float>(true, true));
    }

    @Test(expected = IllegalArgumentException.class)
    public void unlabelledGraphIsRejected() {
        Prim.minimumSpanningForest(new Graph<String, Float>(false, false));
    }

    private static void addEdge(
            Graph<String, Float> graph,
            String start,
            String end,
            float label) {
        graph.addNode(start);
        graph.addNode(end);
        graph.addEdge(start, end, label);
    }

    private static double totalWeight(
            Collection<? extends AbstractEdge<String, Float>> edges) {
        return edges.stream().mapToDouble(edge -> edge.getLabel()).sum();
    }
}
