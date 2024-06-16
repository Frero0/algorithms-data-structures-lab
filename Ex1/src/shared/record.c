#include "record.h"
#include "comparable.h"
#include "free.h"

int compare_records_string(const void *a, const void *b)
{
  struct Record *r1 = (struct Record *)a;
  struct Record *r2 = (struct Record *)b;
  return compare_string(&r1->field1, &r2->field1);
}

int compare_records_int(const void *a, const void *b)
{
  struct Record *record_a = (struct Record *)a;
  struct Record *record_b = (struct Record *)b;
  return compare_int(&record_a->field2, &record_b->field2);
}

int compare_records_float(const void *a, const void *b)
{
  struct Record *record_a = (struct Record *)a;
  struct Record *record_b = (struct Record *)b;
  return compare_float(&record_a->field3, &record_b->field3);
}

void print_records(struct Record *array, int size)
{
  for (int i = 0; i < size; i++)
    printf("%d,%s,%d,%lf\n", array[i].id, array[i].field1, array[i].field2, array[i].field3);
}

void free_record(void *a)
{
  struct Record *r1 = (struct Record *)a;
  free_string(r1->field1);
}
