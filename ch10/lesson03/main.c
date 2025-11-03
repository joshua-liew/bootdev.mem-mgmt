#define MUNIT_ENABLE_ASSERT_ALIASES
#include <stdio.h>
#include <stdlib.h>

#include "munit/munit.h"
#include "snekobject.h"

static MunitResult
test_inc_refcount(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    snek_object_t *obj = new_snek_integer(10);
    assert_int(obj->refcount, ==, 1);

    refcount_inc(obj);
    assert_int(obj->refcount, ==, 2);

    free(obj);
    return MUNIT_OK;
}

static MunitResult
test_inc_refcount_more(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;
    snek_object_t *obj = new_snek_float(4.20);
    assert_int(obj->refcount, ==, 1);

    refcount_inc(obj);
    refcount_inc(obj);
    refcount_inc(obj);
    refcount_inc(obj);
    refcount_inc(obj);
    assert_int(obj->refcount, ==, 6);

    free(obj);
    return MUNIT_OK;
}

static MunitResult
test_null_obj(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    refcount_inc(NULL);
    assert(1);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/test_inc_refcount", test_inc_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_inc_refcount_more", test_inc_refcount_more, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_null_obj", test_null_obj, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/refcount-l3-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
