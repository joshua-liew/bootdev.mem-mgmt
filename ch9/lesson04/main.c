#define MUNIT_ENABLE_ASSERT_ALIASES
#include <stdlib.h>
#include "munit/munit.h"
#include "snekobject.h"

static MunitResult
test_str_copied(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    char *input = "Hello, World!";
    snek_object_t *obj = new_snek_string(input);
    assert_int(obj->kind, ==, STRING);

    // Should not have pointers be the same, otherwise we didn't copy the value.
    assert_ptr_not_equal(obj->data.v_string, input);

    // But should have the same data!
    //  This way the object can free it's own memory later.
    assert_string_equal(obj->data.v_string, input);

    // Free the string, and then free the object.
    free(obj->data.v_string);
    free(obj);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/copies_value", test_str_copied, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/objects-l4-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
