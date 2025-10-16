#include "munit/munit.h"

#include "color.h"

static MunitResult
test_color_enum1(const MunitParameter params[], void* data) {
    // silence compiler warnings
    (void) params;
    (void) data;

    munit_assert_int(RED, ==, 0);
    munit_assert_int(GREEN, ==, 1);
    munit_assert_int(BLUE, ==, 2);

    return MUNIT_OK;
}

static MunitResult
test_color_enum2(const MunitParameter params[], void* data) {
    // silence compiler warnings
    (void) params;
    (void) data;

    munit_assert_int(RED, !=, 4);
    munit_assert_int(GREEN, !=, 2);
    munit_assert_int(BLUE, !=, 0);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/are_defined", test_color_enum1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/are_defined_correctly", test_color_enum2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {

    static const MunitSuite suite = {
        "/enums-l1-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };

    return munit_suite_main(&suite, NULL, 0, NULL);
}

