#define MUNIT_ENABLE_ASSERT_ALIASES
#include <stdlib.h>
#include "munit/munit.h"
#include "snekobject.h"

static MunitResult
test_array(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;
    // Create an array
    snek_object_t *obj = new_snek_array(2);

    // Create some objects to put in the array
    // Can store objects, even though they have different types (just like Python)
    snek_object_t *first = new_snek_string("First");
    snek_object_t *second = new_snek_integer(3);

    assert(snek_array_set(obj, 0, first));
    assert(snek_array_set(obj, 1, second));

    snek_object_t *retrieved_first = snek_array_get(obj, 0);
    assert_not_null(retrieved_first);
    assert_int(retrieved_first->kind, ==, STRING);
    assert_ptr(first, ==, retrieved_first);

    snek_object_t *retrieved_second = snek_array_get(obj, 1);
    assert_not_null(retrieved_second);
    assert_int(retrieved_second->kind, ==, INTEGER);
    assert_ptr(second, ==, retrieved_second);

    free(first->data.v_string);
    free(first);
    free(second);
    free(obj->data.v_array.elements);
    free(obj);
    return MUNIT_OK;
}

static MunitResult
test_set_outside_bounds(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;
    // Create an array
    snek_object_t *obj = new_snek_array(2);

    snek_object_t *outside = new_snek_string("First");

    // Inside of bound
    assert(snek_array_set(obj, 1, outside));

    // Outside of bound
    assert_false(snek_array_set(obj, 100, outside));

    // Free memory
    free(outside->data.v_string);
    free(outside);
    free(obj->data.v_array.elements);
    free(obj);

    return MUNIT_OK;
}

static MunitResult
test_get_outside_bounds(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;
    // Create an array
    snek_object_t *obj = new_snek_array(1);
    snek_object_t *first = new_snek_string("First");
    assert(snek_array_set(obj, 0, first));

    // Outside of bound
    assert_null(snek_array_get(obj, 1));

    free(first->data.v_string);
    free(first);
    free(obj->data.v_array.elements);
    free(obj);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/set_and_get", test_array, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/set_outside", test_set_outside_bounds, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/get_outside", test_get_outside_bounds, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/objects-l7-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
