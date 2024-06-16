package priorityqueue;

public class RecordComparatorStringField {
    public int compare(Record r1, Record r2) {
        int result = (String.CASE_INSENSITIVE_ORDER).compare(r1.getStringField(), r2.getStringField());
          return result;
       }
}
