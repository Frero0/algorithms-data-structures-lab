#include <string.h>

#include "edit_distance.h"
#include "test/unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

static void assert_both_algorithms(const char *first, const char *second, int expected)
{
    TEST_ASSERT_EQUAL_INT(
        expected,
        edit_distance(first, second, strlen(first), strlen(second)));
    TEST_ASSERT_EQUAL_INT(expected, edit_distance_dyn(first, second));
}

static void test_null_parameters(void)
{
    TEST_ASSERT_EQUAL_INT(-1, edit_distance(NULL, NULL, 0, 0));
    TEST_ASSERT_EQUAL_INT(-1, edit_distance_dyn(NULL, NULL));
}

static void test_empty_strings(void)
{
    assert_both_algorithms("", "", 0);
    assert_both_algorithms("", "0123456789", 10);
}

static void test_equal_strings(void)
{
    assert_both_algorithms("pioppo", "pioppo", 0);
}

static void test_assignment_examples(void)
{
    assert_both_algorithms("casa", "cassa", 1);
    assert_both_algorithms("casa", "cara", 2);
    assert_both_algorithms("vinaio", "vino", 2);
    assert_both_algorithms("tassa", "passato", 4);
}

static void test_distance_is_symmetric(void)
{
    int forward = edit_distance_dyn("algoritmo", "algortmo");
    int backward = edit_distance_dyn("algortmo", "algoritmo");
    TEST_ASSERT_EQUAL_INT(forward, backward);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_null_parameters);
    RUN_TEST(test_empty_strings);
    RUN_TEST(test_equal_strings);
    RUN_TEST(test_assignment_examples);
    RUN_TEST(test_distance_is_symmetric);
    return UNITY_END();
}
