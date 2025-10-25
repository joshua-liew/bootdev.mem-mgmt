#include "munit/munit.h"
#include "snekstack.h"

static MunitResult
create_stack_small(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    stack_t* s = stack_new(3);
    munit_assert_int(s->capacity, ==, 3);
    munit_assert_int(s->count, ==, 0);
    munit_assert_ptr_not_null(s->data);

    free(s->data);
    free(s);
    return MUNIT_OK;
}

static MunitResult
create_stack_large(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    stack_t* s = stack_new(100);
    munit_assert_int(s->capacity, ==, 100);
    munit_assert_int(s->count, ==, 0);
    munit_assert_ptr_not_null(s->data);

    free(s->data);
    free(s);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/create_stack_small", create_stack_small, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/create_stack_large", create_stack_large, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/stack-l1-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
