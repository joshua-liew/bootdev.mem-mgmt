#include <stdio.h>

#include "munit/munit.h"
#include "exercise.h"

static MunitResult
test_formats_int1(const MunitParameter params[], void* data) {
    // silence compiler warnings
    (void) params;
    (void) data;

    char buffer[100];
    snek_object_t i = new_integer(5);
    format_object(i, buffer);

    munit_assert_string_equal("int:5", buffer);

    return MUNIT_OK;
}

static MunitResult
test_formats_int2(const MunitParameter params[], void* data) {
    // silence compiler warnings
    (void) params;
    (void) data;

    char buffer[100];
    snek_object_t i = new_integer(2014);
    format_object(i, buffer);

    munit_assert_string_equal("int:2014", buffer);

    return MUNIT_OK;
}

static MunitResult
test_formats_string1(const MunitParameter params[], void* data) {
    // silence compiler warnings
    (void) params;
    (void) data;

    char buffer[100];
    snek_object_t s = new_string("Hello!");
    format_object(s, buffer);

    munit_assert_string_equal("string:Hello!", buffer);

    return MUNIT_OK;
}

static MunitResult
test_formats_string2(const MunitParameter params[], void* data) {
    // silence compiler warnings
    (void) params;
    (void) data;

    char buffer[100];
    snek_object_t s = new_string("nvim btw");
    format_object(s, buffer);

    munit_assert_string_equal("string:nvim btw", buffer);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/integer", test_formats_int1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/string", test_formats_string1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/integer_nvim", test_formats_int2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/string_nvim", test_formats_string2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {

    static const MunitSuite suite = {
        "/unions-l1-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };

    return munit_suite_main(&suite, NULL, 0, NULL);
}

