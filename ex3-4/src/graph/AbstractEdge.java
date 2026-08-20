package graph;

public interface AbstractEdge<V, L> {
    V getStart();

    V getEnd();

    L getLabel();
}
