#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "munit/munit.h"
#include "exercise.h"

static MunitResult
test_swap_str(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    char* a = "Hello";
    char* b = "Goodbye";
    swap_strings(&a, &b);

    munit_assert_string_equal(a, "Goodbye");
    munit_assert_string_equal(b, "Hello");
    return MUNIT_OK;
}

static MunitResult
test_swap_str_long(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    char* a = "terminal.shop";
    char* b = "ssh";
    swap_strings(&a, &b);

    munit_assert_string_equal(a, "ssh");
    munit_assert_string_equal(b, "terminal.shop");
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/swap_str", test_swap_str, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/swap_str_long", test_swap_str_long, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/advancedptrs-l5-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
