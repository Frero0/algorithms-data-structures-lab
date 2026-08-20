package priorityqueue;

public interface AbstractQueue<E> {
    boolean empty();

    boolean push(E element);

    boolean contains(E element);

    E top();

    void pop();

    boolean remove(E element);
}
