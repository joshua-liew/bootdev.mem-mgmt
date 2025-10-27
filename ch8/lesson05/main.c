#define MUNIT_ENABLE_ASSERT_ALIASES
#include "exercise.h"
#include "munit/munit.h"
#include "snekstack.h"

static MunitResult
heterogenous_stack(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;
    stack_t *s = stack_new(2);
    assert_ptr_not_null(s);

    scary_double_push(s);
    assert_int(s->count, ==, 2);

    int value = (int)s->data[0];
    assert_int(value, ==, 1337);

    int *pointer = s->data[1];
    assert_int(*pointer, ==, 1024);

    free(pointer);
    stack_free(s);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/heterogenous_stack", heterogenous_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/stack-l5-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
