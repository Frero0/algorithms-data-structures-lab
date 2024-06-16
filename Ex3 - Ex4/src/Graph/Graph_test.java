package Graph;

import java.util.*;
import static org.junit.Assert.*;
import org.junit.Before;
import org.junit.Test;

import My_Exception.GraphException;

public class Graph_test {
    private Graph<String, Integer> graph;

    @Before
    public void createGraph() throws GraphException {
        graph = new Graph<>(false, true);
        graph.addNode("A");
        graph.addNode("B");
        graph.addEdge("A", "B", 1);
        graph.addNode("C");
    }

    @Test
    public void testAddNode() {
        assertTrue(graph.addNode("G"));
        assertTrue(graph.containsNode("G"));
        assertFalse(graph.addNode("A")); // "A" già esiste nel grafo
    }

    @Test
    public void testAddEdge() {
        assertTrue(graph.addEdge("A", "C", 2));
        assertTrue(graph.containsEdge("A", "C"));
        assertFalse(graph.addEdge("A", "D", 3)); // "D" non esiste nel grafo
    }

    @Test
    public void testRemoveNode() {
        assertTrue(graph.removeNode("B"));
        assertFalse(graph.containsNode("B"));
        assertFalse(graph.removeNode("D")); // "D" non esiste nel grafo
    }

    @Test
    public void testRemoveEdge() {
        assertTrue(graph.removeEdge("A", "B"));
        assertFalse(graph.containsEdge("A", "B"));
        assertFalse(graph.removeEdge("A", "D")); // "D" non esiste nel grafo
    }

    @Test
    public void testGetLabel() {
        assertEquals(Integer.valueOf(1), graph.getLabel("A", "B"));
        assertNull(graph.getLabel("A", "D")); // "D" non esiste nel grafo
    }

    @Test
    public void testNumNodes() {
        assertEquals(3, graph.numNodes());
    }

    @Test
    public void testNumEdges() {
        assertEquals(1, graph.numEdges());
    }

    @Test
    public void testGetNodes() {
        Collection<String> nodes = graph.getNodes();
        assertTrue(nodes.contains("A"));
        assertTrue(nodes.contains("B"));
    }

    @Test
    public void testGetEdges() {
        Collection<? extends AbstractEdge<String, Integer>> edges = graph.getEdges();
        assertEquals(2, edges.size());
    }

    @Test
    public void testGetNeighbours() {
        Collection<String> neighbours = graph.getNeighbours("A");
        assertTrue(neighbours.contains("B"));
    }
}