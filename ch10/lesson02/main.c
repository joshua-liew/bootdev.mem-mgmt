#define MUNIT_ENABLE_ASSERT_ALIASES
#include <stdio.h>
#include <stdlib.h>

#include "munit/munit.h"
#include "snekobject.h"

static MunitResult
test_int_has_refcount(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    snek_object_t *obj = new_snek_integer(10);
    assert_int(obj->refcount, ==, 1);
    free(obj);

    return MUNIT_OK;
}

static MunitResult
test_float_has_refcount(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    snek_object_t *obj = new_snek_float(42.0);
    assert_int(obj->refcount, ==, 1);
    free(obj);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/int_refcount", test_int_has_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/float_refcount", test_float_has_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/refcount-l2-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
