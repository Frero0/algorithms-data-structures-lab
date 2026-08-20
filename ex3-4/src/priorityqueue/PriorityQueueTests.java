package priorityqueue;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.Arrays;
import java.util.Comparator;

import org.junit.Before;
import org.junit.Test;

public class PriorityQueueTests {
    private PriorityQueue<Integer> queue;

    @Before
    public void createQueue() {
        queue = new PriorityQueue<>(Comparator.naturalOrder());
    }

    @Test
    public void newQueueIsEmpty() {
        assertTrue(queue.empty());
    }

    @Test
    public void pushMaintainsMinimumAtTop() {
        assertTrue(queue.push(7));
        assertEquals(Integer.valueOf(7), queue.top());
        assertTrue(queue.push(3));
        assertEquals(Integer.valueOf(3), queue.top());
        assertTrue(queue.push(9));
        assertTrue(queue.push(1));
        assertEquals(Integer.valueOf(1), queue.top());
    }

    @Test
    public void duplicateElementsAreRejected() {
        assertTrue(queue.push(3));
        assertFalse(queue.push(3));
    }

    @Test
    public void popRemovesMembershipAndAllowsReinsertion() {
        queue.addAll(Arrays.asList(7, 3, 9, 1));

        queue.pop();

        assertEquals(Integer.valueOf(3), queue.top());
        assertFalse(queue.contains(1));
        assertTrue(queue.push(1));
        assertEquals(Integer.valueOf(1), queue.top());
    }

    @Test
    public void removeUpdatesMembershipAndHeapOrder() {
        queue.addAll(Arrays.asList(7, 3, 9, 1, 5));

        assertTrue(queue.remove(7));
        assertFalse(queue.contains(7));
        assertFalse(queue.remove(7));
        assertTrue(queue.push(7));

        int[] expected = {1, 3, 5, 7, 9};
        for (int value : expected) {
            assertEquals(Integer.valueOf(value), queue.top());
            queue.pop();
        }
        assertTrue(queue.empty());
    }

    @Test
    public void addAllUsesPriorityOrder() {
        queue.addAll(Arrays.asList(8, 4, 6, 2));
        assertEquals(Integer.valueOf(2), queue.top());
        assertTrue(queue.contains(8));
    }

    @Test(expected = PriorityQueueException.class)
    public void topRejectsEmptyQueue() {
        queue.top();
    }

    @Test(expected = PriorityQueueException.class)
    public void popRejectsEmptyQueue() {
        queue.pop();
    }

    @Test(expected = PriorityQueueException.class)
    public void pushRejectsNullElements() {
        queue.push(null);
    }

    @Test(expected = PriorityQueueException.class)
    public void constructorRejectsNullComparator() {
        new PriorityQueue<Integer>(null);
    }
}
