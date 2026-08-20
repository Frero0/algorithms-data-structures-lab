package priorityqueue;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * A min-priority queue backed by a binary heap.
 *
 * <p>The map stores each element's current heap index, allowing constant-time
 * membership checks and logarithmic removals. Duplicate and null elements are
 * not accepted.</p>
 */
public class PriorityQueue<E> implements AbstractQueue<E> {
    private final Comparator<? super E> comparator;
    private final List<E> heap;
    private final Map<E, Integer> indices;

    public PriorityQueue(Comparator<? super E> comparator) {
        if (comparator == null) {
            throw new PriorityQueueException("The comparator cannot be null");
        }
        this.comparator = comparator;
        this.heap = new ArrayList<>();
        this.indices = new HashMap<>();
    }

    @Override
    public boolean empty() {
        return heap.isEmpty();
    }

    @Override
    public boolean push(E element) {
        requireElement(element);
        if (indices.containsKey(element)) {
            return false;
        }

        heap.add(element);
        int index = heap.size() - 1;
        indices.put(element, index);
        siftUp(index);
        return true;
    }

    @Override
    public boolean contains(E element) {
        requireElement(element);
        return indices.containsKey(element);
    }

    @Override
    public E top() {
        requireNotEmpty("Cannot read the top of an empty priority queue");
        return heap.get(0);
    }

    @Override
    public void pop() {
        requireNotEmpty("Cannot remove the top of an empty priority queue");
        removeAt(0);
    }

    @Override
    public boolean remove(E element) {
        requireElement(element);
        Integer index = indices.get(element);
        if (index == null) {
            return false;
        }

        removeAt(index);
        return true;
    }

    public void addAll(Collection<? extends E> elements) {
        if (elements == null) {
            throw new PriorityQueueException("The collection cannot be null");
        }
        for (E element : elements) {
            push(element);
        }
    }

    private void removeAt(int index) {
        int lastIndex = heap.size() - 1;
        E removed = heap.get(index);
        E last = heap.remove(lastIndex);
        indices.remove(removed);

        if (index == lastIndex) {
            return;
        }

        heap.set(index, last);
        indices.put(last, index);

        int parentIndex = (index - 1) / 2;
        if (index > 0 && comparator.compare(heap.get(index), heap.get(parentIndex)) < 0) {
            siftUp(index);
        } else {
            siftDown(index);
        }
    }

    private void siftUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (comparator.compare(heap.get(index), heap.get(parentIndex)) >= 0) {
                return;
            }
            swap(index, parentIndex);
            index = parentIndex;
        }
    }

    private void siftDown(int index) {
        while (true) {
            int leftIndex = 2 * index + 1;
            if (leftIndex >= heap.size()) {
                return;
            }

            int rightIndex = leftIndex + 1;
            int smallestIndex = leftIndex;
            if (rightIndex < heap.size()
                    && comparator.compare(heap.get(rightIndex), heap.get(leftIndex)) < 0) {
                smallestIndex = rightIndex;
            }

            if (comparator.compare(heap.get(index), heap.get(smallestIndex)) <= 0) {
                return;
            }
            swap(index, smallestIndex);
            index = smallestIndex;
        }
    }

    private void swap(int firstIndex, int secondIndex) {
        E first = heap.get(firstIndex);
        E second = heap.get(secondIndex);
        heap.set(firstIndex, second);
        heap.set(secondIndex, first);
        indices.put(second, firstIndex);
        indices.put(first, secondIndex);
    }

    private void requireElement(E element) {
        if (element == null) {
            throw new PriorityQueueException("Null elements are not supported");
        }
    }

    private void requireNotEmpty(String message) {
        if (empty()) {
            throw new PriorityQueueException(message);
        }
    }
}
