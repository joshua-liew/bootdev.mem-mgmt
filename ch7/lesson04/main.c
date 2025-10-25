#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "munit/munit.h"
#include "exercise.h"

static MunitResult
test_swap_ints(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    int a = 5;
    int b = 6;
    swap_ints(&a, &b);

    munit_assert_int(a, ==, 6);
    munit_assert_int(b, ==, 5);
    return MUNIT_OK;
}

static MunitResult
test_swap_ints_same(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    int a = 5;
    swap_ints(&a, &a);

    munit_assert_int(a, ==, 5);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/test_swap_ints", test_swap_ints, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_swap_ints_same", test_swap_ints_same, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/advancedptrs-l4-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
