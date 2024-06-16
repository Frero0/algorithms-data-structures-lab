package priorityqueue;

import java.util.Comparator;

public class RecordComparatorIntField implements Comparator<Record>{
    public int compare(Record r1, Record r2) {
        int result = (Integer.valueOf(r1.getIntegerField()).compareTo(r2.getIntegerField()));
          return result;
       }
}
