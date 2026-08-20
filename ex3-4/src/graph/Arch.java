package graph;

import java.util.Objects;

public final class Arch<V, L> implements AbstractEdge<V, L> {
    private final V start;
    private final V end;
    private final L label;

    public Arch(V start, V end, L label) {
        this.start = Objects.requireNonNull(start, "The start node cannot be null");
        this.end = Objects.requireNonNull(end, "The end node cannot be null");
        this.label = label;
    }

    public Arch(V start, V end) {
        this(start, end, null);
    }

    @Override
    public V getStart() {
        return start;
    }

    @Override
    public V getEnd() {
        return end;
    }

    @Override
    public L getLabel() {
        return label;
    }

    @Override
    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (!(other instanceof Arch<?, ?>)) {
            return false;
        }
        Arch<?, ?> edge = (Arch<?, ?>) other;
        return Objects.equals(start, edge.start) && Objects.equals(end, edge.end);
    }

    @Override
    public int hashCode() {
        return Objects.hash(start, end);
    }

    @Override
    public String toString() {
        return start + "," + end + "," + label;
    }
}
