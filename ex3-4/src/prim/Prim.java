package prim;

import graph.AbstractEdge;
import graph.Graph;
import priorityqueue.PriorityQueue;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public final class Prim {
    private Prim() {}

    public static <V, L extends Number & Comparable<L>>
            Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(Graph<V, L> graph) {
        if (graph == null || graph.isDirected() || !graph.isLabelled()) {
            throw new IllegalArgumentException(
                    "Prim requires a non-null, undirected and labelled graph");
        }

        Set<V> visited = new HashSet<>();
        PriorityQueue<AbstractEdge<V, L>> queue = new PriorityQueue<>(
                Comparator.comparing(AbstractEdge::getLabel));
        List<AbstractEdge<V, L>> forest = new ArrayList<>();

        for (V root : graph.getNodes()) {
            if (visited.contains(root)) {
                continue;
            }

            visited.add(root);
            queue.addAll(graph.getEdgesFrom(root));
            while (!queue.empty()) {
                AbstractEdge<V, L> edge = queue.top();
                queue.pop();

                boolean startVisited = visited.contains(edge.getStart());
                boolean endVisited = visited.contains(edge.getEnd());
                if (startVisited == endVisited) {
                    continue;
                }

                V next = startVisited ? edge.getEnd() : edge.getStart();
                visited.add(next);
                forest.add(edge);
                queue.addAll(graph.getEdgesFrom(next));
            }
        }

        return forest;
    }

    static Graph<String, Float> readGraph(Path path) throws IOException {
        Graph<String, Float> graph = new Graph<>(false, true);
        try (BufferedReader reader = Files.newBufferedReader(path)) {
            String line;
            int lineNumber = 0;
            while ((line = reader.readLine()) != null) {
                lineNumber++;
                if (line.isBlank()) {
                    continue;
                }

                String[] fields = line.split(",", -1);
                if (fields.length != 3) {
                    throw new IOException("Invalid CSV record at line " + lineNumber);
                }

                String start = fields[0].trim();
                String end = fields[1].trim();
                float distance;
                try {
                    distance = Float.parseFloat(fields[2].trim());
                } catch (NumberFormatException exception) {
                    throw new IOException("Invalid distance at line " + lineNumber, exception);
                }

                if (start.isEmpty() || end.isEmpty() || !Float.isFinite(distance) || distance < 0) {
                    throw new IOException("Invalid graph data at line " + lineNumber);
                }

                graph.addNode(start);
                graph.addNode(end);
                graph.addEdge(start, end, distance);
            }
        }
        return graph;
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java prim.Prim <graph.csv>");
            System.exit(1);
        }

        try {
            Graph<String, Float> graph = readGraph(Path.of(args[0]));
            Collection<? extends AbstractEdge<String, Float>> forest =
                    minimumSpanningForest(graph);

            for (AbstractEdge<String, Float> edge : forest) {
                System.out.println(edge);
            }

            double totalWeight = forest.stream()
                    .mapToDouble(edge -> edge.getLabel().doubleValue())
                    .sum();
            System.err.println("Nodes in the graph: " + graph.numNodes());
            System.err.println("Edges in the forest: " + forest.size());
            System.err.println("Total weight: " + totalWeight);
        } catch (IOException | IllegalArgumentException exception) {
            System.err.println("Cannot process graph: " + exception.getMessage());
            System.exit(1);
        }
    }
}
