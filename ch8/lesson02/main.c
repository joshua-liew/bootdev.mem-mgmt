#include "munit/munit.h"
#include "snekstack.h"

static MunitResult
create_stack(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    stack_t* s = stack_new(10);
    munit_assert_ptr_not_null(s);
    munit_assert_int(s->capacity, ==, 10);
    munit_assert_int(s->count, ==, 0);
    munit_assert_ptr_not_null(s->data);

    free(s->data);
    free(s);
    return MUNIT_OK;
}

static MunitResult
push_stack(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    stack_t* s = stack_new(2);
    // Create stack assertions
    munit_assert_ptr_not_null(s);
    munit_assert_int(s->capacity, ==, 2);
    munit_assert_int(s->count, ==, 0);
    munit_assert_ptr_not_null(s->data);
    
    int a = 1;
    // Push to stack assertions
    stack_push(s, &a);
    munit_assert_int(s->count, ==, 1);
    stack_push(s, &a);
    munit_assert_int(s->count, ==, 2);
    munit_assert_int(s->capacity, ==, 2);
    munit_assert_ptr_equal(s->data[0], &a);
    munit_assert_ptr_equal(s->data[1], &a);

    free(s->data);
    free(s);
    return MUNIT_OK;
}

static MunitResult
push_double_capacity(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    stack_t* s = stack_new(2);
    // Create stack assertions
    munit_assert_ptr_not_null(s);
    munit_assert_int(s->capacity, ==, 2);
    munit_assert_int(s->count, ==, 0);
    munit_assert_ptr_not_null(s->data);
    
    int a = 1;
    stack_push(s, &a);
    stack_push(s, &a);
    // Push to stack assertions
    munit_assert_int(s->capacity, ==, 2);
    munit_assert_int(s->count, ==, 2);
    munit_assert_ptr_equal(s->data[0], &a);
    munit_assert_ptr_equal(s->data[1], &a);

    // Double capacity assertion
    int b = 2;
    stack_push(s, &b);
    munit_assert_ptr_not_null(s);
    munit_assert_int(s->capacity, ==, 4);
    munit_assert_int(s->count, ==, 3);
    munit_assert_ptr_equal(s->data[2], &b);

    free(s->data);
    free(s);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/create_stack", create_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/push_stack", push_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/push_double_capacity", push_double_capacity, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/stack-l2-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
