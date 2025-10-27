#define MUNIT_ENABLE_ASSERT_ALIASES
#include "exercise.h"
#include "munit/munit.h"
#include "snekstack.h"

static MunitResult
multiple_types_stack(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;
    stack_t *s = stack_new(4);
    assert_ptr_not_null(s);
    
    stack_push_multiple_types(s);
    assert_int(s->count, ==, 2);

    float *f = s->data[0];
    assert_float(*f, ==, 3.14);
    char *string = s->data[1];
    assert_string_equal(string, "Sneklang is blazingly slow!");

    free(f);
    free(string);
    stack_free(s);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/multiple_types_stack", multiple_types_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/stack-l6-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
