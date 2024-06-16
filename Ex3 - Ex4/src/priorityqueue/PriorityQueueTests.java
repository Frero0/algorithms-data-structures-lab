package priorityqueue;

import java.util.*;

import java.util.Comparator;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;

public class PriorityQueueTests {

    private Record record1, record2, record3;
    private PriorityQueue<Record> priorityQueue;

    @Before
    public void createOrderedArray() throws PriorityQueueException {
        record1 = new Record(-12);
        record2 = new Record(0);
        record3 = new Record(4);

        Comparator<Record> comparator = new RecordComparatorIntField();
        priorityQueue = new PriorityQueue<>(comparator);
    }

    @Test
    public void testIsEmpty_zeroEl() {
        assertTrue(priorityQueue.empty());
    }

    @Test
    public void testIsEmpty_oneEl() throws Exception {
        priorityQueue.push(record1);
        assertFalse(priorityQueue.empty());
    }

    @Test
    // It directly accesses the OrderedArray instance variable orderedArray.array
    public void testAdd_oneEl() throws Exception {
        priorityQueue.push(record1);
        assertTrue(record1 == priorityQueue.top());
    }

    @Test
    public void testGet_oneEl() throws Exception {
        priorityQueue.queue.add(record1);
        assertTrue(record1 == priorityQueue.top());
    }

    @Test
    // It directly access the instance variable orderedArray.array
    public void testAdd_threeEl_1() throws Exception {

        Record[] arrExpected = { record1, record2, record3 };

        priorityQueue.push(record2);
        priorityQueue.push(record1);
        priorityQueue.push(record3);

        assertArrayEquals(arrExpected, priorityQueue.queue.toArray());
    }

    @Test
    public void tesAdd_threeEl_2() throws Exception {

        Record[] arrExpected = { record1, record2, record3 };

        priorityQueue.push(record2);
        priorityQueue.push(record1);
        priorityQueue.push(record3);

        Record[] arrActual = new Record[3];

        for (int i = 0; i < 3; i++)
            arrActual[i] = priorityQueue.queue.get(i);

        assertArrayEquals(arrExpected, arrActual);
    }

}
