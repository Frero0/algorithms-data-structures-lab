/* #define UNITY_INCLUDE_DOUBLE */

#include "test/unity/unity.h"

#include "headers/merge_sort.h"
#include "shared/record.h"

void setUp(void) {}
void tearDown(void) {}

void test_null_array(void)
{
  int *actual = NULL;
  TEST_ASSERT_NULL(actual);
  merge_sort_wrapper(actual, 0, 0, compare_int);
  TEST_ASSERT_NULL(actual);
}

void test_int_array(void)
{
  int actual[] = {6, 3, 2, 657, 23, 4534, 1, 33, 443, 55, 77};
  int expected[] = {1, 2, 3, 6, 23, 33, 55, 77, 443, 657, 4534};
  merge_sort_wrapper(actual, 11, sizeof(actual[0]), compare_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, 11);
}

void test_long_array(void)
{
  long actual[] = {LONG_MAX, 0, LONG_MIN, 40, 21, 18, 58, 118, 98};
  long expected[] = {LONG_MIN, 0, 18, 21, 40, 58, 98, 118, LONG_MAX};
  merge_sort_wrapper(actual, 9, sizeof(actual[0]), compare_long);
  TEST_ASSERT_EQUAL_INT32_ARRAY(expected, actual, 9);
}

void test_float_array(void)
{
  float actual[] = {0.0f, 0.58f, 0.42f, 98.31f, 15.42f, 0.18f, 0.21f, 0.40f, 0.401f};
  float expected[] = {0.0f, 0.18f, 0.21f, 0.40f, 0.401f, 0.42f, 0.58f, 15.42f, 98.31f};
  merge_sort_wrapper(actual, 9, sizeof(actual[0]), compare_float);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, 9);
}

void test_char_array(void)
{
  char actual[] = {'d', 'c', 'a', 'b', 'f', 'e', 'g', 'i', 'h', 'l'};
  char expected[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'l'};
  merge_sort_wrapper(actual,  9, sizeof(actual[0]), compare_char);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expected, actual, 9);
}

void test_string_array(void)
{
  char *actual[9] = {"ss\0", "xx\0", "uu\0", "vv\0", "sn\0", "bs\0", "sv\0", "sf\0", "sr\0"};
  char *expected[9] = {"bs\0", "sf\0", "sn\0", "sr\0", "ss\0", "sv\0", "uu\0", "vv\0", "xx\0"};
  merge_sort_wrapper(actual, 9, sizeof(actual[0]), compare_string);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, 9);
}

void test_array_with_only_duplicated_elements(void)
{
  int actual[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int expected[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  merge_sort_wrapper(actual, 10, sizeof(actual[0]), compare_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, 10);
}

void test_already_sorted_array(void)
{
  int actual[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  merge_sort_wrapper(actual, 10, sizeof(actual[0]), compare_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, 10);
}

void test_negative_int_array(void)
{
  int actual[] = {-1, -5, -9, -2, -3, -14, -10, -18, -21};
  int expected[] = {-21, -18, -14, -10, -9, -5, -3, -2, -1};
  merge_sort_wrapper(actual, 9, sizeof(actual[0]),  compare_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, 9);
}

void test_records_array(void)
{

  struct Record actual[] = {
      {7, "a\0", 1, 0.0001f},
      {2, "c\0", 0, 1.0001f},
      {0, "a\0", 0, 0.0211f},
      {4, "b\0", 24, 0.0001f},
      {3, "b\0", 15, 0.0001f},
      {5, "c\0", 0, 0.0001f},
      {1, "d\0", 0, 0.0001f},
      {6, "a\0", 0, 0.0001f},
      {8, "d\0", 0, 0.0002f},
  };

  struct Record expected[] = {
      {0, "a\0", 0, 0.0001f},
      {1, "a\0", 0, 0.0001f},
      {2, "a\0", 0, 0.0001f},
      {3, "b\0", 0, 0.0001f},
      {4, "b\0", 0, 0.0001f},
      {5, "c\0", 0, 0.0001f},
      {6, "c\0", 1, 0.0002f},
      {7, "d\0", 15, 0.0211f},
      {8, "d\0", 24, 1.0001f},
  };

  merge_sort_wrapper(actual, 9, sizeof(actual[0]),  compare_records_string);
  for (unsigned long i = 0; i < sizeof(actual) / sizeof(actual[0]); i++)
  {
    TEST_ASSERT_EQUAL_STRING(expected[i].field1, actual[i].field1);
  }
  merge_sort_wrapper(actual, 9, sizeof(actual[0]),  compare_records_int);
  for (unsigned long i = 0; i < sizeof(actual) / sizeof(actual[0]); i++)
  {
    TEST_ASSERT_EQUAL_INT(expected[i].field2, actual[i].field2);
  }
  merge_sort_wrapper(actual, 9, sizeof(actual[0]),  compare_records_float);
  for (unsigned long i = 0; i < sizeof(actual) / sizeof(actual[0]); i++)
  {
    TEST_ASSERT_EQUAL_FLOAT(expected[i].field3, actual[i].field3);
  }
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_null_array);
  RUN_TEST(test_int_array);
  //RUN_TEST(test_double_array);
  RUN_TEST(test_long_array);
  RUN_TEST(test_float_array);
  RUN_TEST(test_char_array);
  RUN_TEST(test_string_array);
  RUN_TEST(test_array_with_only_duplicated_elements);
  RUN_TEST(test_already_sorted_array);
  RUN_TEST(test_negative_int_array);
  RUN_TEST(test_records_array);

  return UNITY_END();
}