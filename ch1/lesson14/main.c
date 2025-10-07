#include "munit/munit.h"

#include "exercise.h"

static MunitResult
test_get_average(const MunitParameter params[], void* data) {
    // silence compiler warnings
    (void) params;
    (void) data;

    float result = get_average(3, 4, 5);
    munit_assert_double_equal(result, 4.0, 9);

    return MUNIT_OK;
}

static MunitResult
test_non_integer(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;

    float result = get_average(3, 3, 5);
    munit_assert_double_equal(result, 11.0 / 3.0, 5);

    return MUNIT_OK;
}

static MunitResult
test_average_of_same(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;

    float result = get_average(10, 10, 10);
    munit_assert_double_equal(result, 10.0, 9);

    return MUNIT_OK;
}

static MunitResult
test_average_of_big_numbers(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;

    float result = get_average(1050, 2050, 2075);
    munit_assert_double_equal(result, 1725.0, 9);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/get_average", test_get_average, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/non_integer", test_non_integer, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/average_of_same", test_average_of_same, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/average_of_big_numbers", test_average_of_big_numbers, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {

    static const MunitSuite suite = {
        "/lesson14-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };

    return munit_suite_main(&suite, NULL, 0, NULL);
}
