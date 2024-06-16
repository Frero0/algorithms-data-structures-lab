package priorityqueue;
import java.util.*;


public interface AbstractQueue<E> {
    boolean empty();
    boolean push(E e);
	boolean contains(E e);
	E top();
	void pop();
	boolean remove(E e);
}



