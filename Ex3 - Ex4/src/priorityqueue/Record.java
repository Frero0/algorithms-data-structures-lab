package priorityqueue;

public class Record {
  private String stringField = null;
  private int integerField;

  public Record(int integerField) {
    this.integerField = integerField;
  }

  public Record(String stringField) {
    this.stringField = stringField;
  }

  public String getStringField() {
    return this.stringField;
  }

  public int getIntegerField() {
    return this.integerField;
  }

}
