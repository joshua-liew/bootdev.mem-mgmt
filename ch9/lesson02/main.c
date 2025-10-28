#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "snekobject.h"

static MunitResult
test_positive(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    snek_object_t *int_object = new_snek_integer(42);
    assert_int(int_object->data.v_int, ==, 42);
    free(int_object);

    return MUNIT_OK;
}

static MunitResult
test_zero(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    snek_object_t *int_object = new_snek_integer(0);
    assert_int(int_object->data.v_int, ==, 0);
    free(int_object);

    return MUNIT_OK;
}

static MunitResult
test_negative(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    snek_object_t *int_object = new_snek_integer(-5);
    assert_int(int_object->data.v_int, ==, -5);
    free(int_object);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/positive", test_positive, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/zero", test_zero, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/negative", test_negative, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/objects-l2-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
