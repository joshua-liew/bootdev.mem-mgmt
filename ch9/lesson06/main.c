#define MUNIT_ENABLE_ASSERT_ALIASES
#include <stdlib.h>
#include "munit/munit.h"
#include "snekobject.h"

static MunitResult
test_create_empty_array(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;
    snek_object_t *obj = new_snek_array(2);
    assert_int(obj->kind, ==, ARRAY);
    assert_int(obj->data.v_array.size, ==, 2);

    free(obj->data.v_array.elements);
    free(obj);
    return MUNIT_OK;
}

static MunitResult
test_used_calloc(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;
    snek_object_t *obj = new_snek_array(2);
    munit_assert_ptr_null(obj->data.v_array.elements[0]);
    munit_assert_ptr_null(obj->data.v_array.elements[0]);

    free(obj->data.v_array.elements);
    free(obj);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/empty", test_create_empty_array, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/calloc", test_used_calloc, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/objects-l6-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
