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
test_inc_refcount(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;
    snek_object_t *obj = new_snek_float(4.20);
    assert_int(obj->refcount, ==, 1);

    refcount_inc(obj);
    assert_int(obj->refcount, ==, 2);

    free(obj);
    return MUNIT_OK;
}

static MunitResult
test_dec_refcount(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;
    snek_object_t *obj = new_snek_float(4.20);

    refcount_inc(obj);
    assert_int(obj->refcount, ==, 2);

    refcount_dec(obj);
    assert_int(obj->refcount, ==, 1);

    // Object is still alive, so we will free manually.
    free(obj);
    return MUNIT_OK;
}

static MunitResult
test_refcount_free_is_called(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;
  snek_object_t *obj = new_snek_float(4.20);

    refcount_inc(obj);
    assert_int(obj->refcount, ==, 2);

    refcount_dec(obj);
    assert_int(obj->refcount, ==, 1);

    refcount_dec(obj);
    return MUNIT_OK;
}

static MunitResult
test_allocated_string_is_freed(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;
    snek_object_t *obj = new_snek_string("Hello @wagslane!");

    refcount_inc(obj);
    assert_int(obj->refcount, ==, 2);

    refcount_dec(obj);
    assert_int(obj->refcount, ==, 1);
    assert_string_equal(obj->data.v_string, "Hello @wagslane!");

    refcount_dec(obj);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/has_refcount", test_int_has_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/inc_refcount", test_inc_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/dec_refcount", test_dec_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/free_refcount", test_refcount_free_is_called, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/string_freed", test_allocated_string_is_freed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/refcount-l4-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
