#include <stdio.h>
#include "munit/munit.h"
#include "exercise.h"

static MunitResult
test_allocate_scalar_array_size(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    int size = 5;
    int multiplier = 2;
    int* result = allocate_scalar_array(size, multiplier);
    munit_assert_ptr_not_null(result);
    munit_assert_not_null(result);
    free(result);

    return MUNIT_OK;
}

static MunitResult
test_allocate_scalar_array_values(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    int size = 5;
    int multiplier = 2;
    int* result = allocate_scalar_array(size, multiplier);
    int expected[5];
    expected[0] = 0;
    expected[1] = 2;
    expected[2] = 4;
    expected[3] = 6;
    expected[4] = 8;
    for (int i = 0; i < size; i++) {
        munit_assert_int(result[i], ==, expected[i]);
    }
    free(result);

    return MUNIT_OK;
}

static MunitResult
test_allocate_scalar_array_zero_multiplier(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    int size = 3;
    int multiplier = 0;
    int* result = allocate_scalar_array(size, multiplier);
    for (int i = 0; i < size; i++) {
        munit_assert_int(result[i], ==, 0);
    }
    free(result);

    return MUNIT_OK;
}

static MunitResult
test_allocate_too_much(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    int size = 1024 * 1024 * 100;
    int multiplier = 1;
    int* result = allocate_scalar_array(size, multiplier);
    munit_assert_ptr_null(result);
    free(result);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/allocate_scalar_array_size", test_allocate_scalar_array_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/allocate_scalar_array_values", test_allocate_scalar_array_values, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/allocate_scalar_array_zero_multiplier", test_allocate_scalar_array_zero_multiplier, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/allocate_too_much", test_allocate_too_much, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/stackheap-l6-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
