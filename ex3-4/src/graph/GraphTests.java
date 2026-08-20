package graph;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

public class GraphTests {
    @Test
    public void constructorPreservesGraphModes() {
        Graph<String, Integer> graph = new Graph<>(true, false);
        assertTrue(graph.isDirected());
        assertFalse(graph.isLabelled());
    }

    @Test
    public void nodesAreUniqueAndNullIsRejected() {
        Graph<String, Integer> graph = new Graph<>(false, true);
        assertTrue(graph.addNode("A"));
        assertFalse(graph.addNode("A"));
        assertFalse(graph.addNode(null));
        assertEquals(1, graph.numNodes());
    }

    @Test
    public void edgeRequiresExistingNodes() {
        Graph<String, Integer> graph = new Graph<>(false, true);
        graph.addNode("A");
        assertFalse(graph.addEdge("A", "B", 1));
        assertEquals(0, graph.numEdges());
    }

    @Test
    public void undirectedEdgeIsVisibleInBothDirections() {
        Graph<String, Integer> graph = new Graph<>(false, true);
        graph.addNode("A");
        graph.addNode("B");
        assertTrue(graph.addEdge("A", "B", 5));
        assertTrue(graph.containsEdge("A", "B"));
        assertTrue(graph.containsEdge("B", "A"));
        assertEquals(1, graph.numEdges());
        assertEquals(2, graph.getEdges().size());
    }

    @Test
    public void directedEdgeIsVisibleOnlyForward() {
        Graph<String, Integer> graph = new Graph<>(true, true);
        graph.addNode("A");
        graph.addNode("B");
        assertTrue(graph.addEdge("A", "B", 5));
        assertTrue(graph.containsEdge("A", "B"));
        assertFalse(graph.containsEdge("B", "A"));
        assertEquals(1, graph.getEdges().size());
    }

    @Test
    public void duplicateEndpointsAreRejected() {
        Graph<String, Integer> graph = new Graph<>(false, true);
        graph.addNode("A");
        graph.addNode("B");
        assertTrue(graph.addEdge("A", "B", 5));
        assertFalse(graph.addEdge("A", "B", 7));
        assertEquals(1, graph.numEdges());
    }

    @Test
    public void graphModesControlLabels() {
        Graph<String, Integer> labelled = new Graph<>(true, true);
        labelled.addNode("A");
        labelled.addNode("B");
        assertFalse(labelled.addEdge("A", "B", null));

        Graph<String, Integer> unlabelled = new Graph<>(true, false);
        unlabelled.addNode("A");
        unlabelled.addNode("B");
        assertTrue(unlabelled.addEdge("A", "B", 42));
        assertNull(unlabelled.getLabel("A", "B"));
    }

    @Test
    public void removeEdgeRemovesBothDirections() {
        Graph<String, Integer> graph = new Graph<>(false, true);
        graph.addNode("A");
        graph.addNode("B");
        graph.addEdge("A", "B", 5);
        assertTrue(graph.removeEdge("A", "B"));
        assertFalse(graph.containsEdge("A", "B"));
        assertFalse(graph.containsEdge("B", "A"));
        assertEquals(0, graph.numEdges());
    }

    @Test
    public void removeNodeRemovesIncidentEdges() {
        Graph<String, Integer> graph = new Graph<>(true, true);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addEdge("A", "B", 1);
        graph.addEdge("C", "B", 2);
        assertTrue(graph.removeNode("B"));
        assertEquals(2, graph.numNodes());
        assertEquals(0, graph.numEdges());
    }

    @Test
    public void neighboursAndLabelsAreReturned() {
        Graph<String, Integer> graph = new Graph<>(false, true);
        graph.addNode("A");
        graph.addNode("B");
        graph.addEdge("A", "B", 5);
        assertTrue(graph.getNeighbours("A").contains("B"));
        assertEquals(Integer.valueOf(5), graph.getLabel("A", "B"));
    }
}
