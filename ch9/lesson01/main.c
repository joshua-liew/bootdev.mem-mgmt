#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "snekobject.h"

static MunitResult
test_integer_constant(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;
    assert_int(INTEGER, ==, 0);

    return MUNIT_OK;
}

static MunitResult
test_integer_obj(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    obj->kind = INTEGER;
    obj->data.v_int = 0;
    assert_int(obj->kind, ==, INTEGER);
    assert_int(obj->data.v_int, ==, 0);

    free(obj);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/integer_constant", test_integer_constant, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/integer_obj", test_integer_obj, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/objects-l1-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
