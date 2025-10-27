#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "snekstack.h"

static MunitResult
pop_stack(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    stack_t* s = stack_new(2);
    munit_assert_ptr_not_null(s);
    munit_assert_int(s->capacity, ==, 2);
    munit_assert_int(s->count, ==, 0);
    munit_assert_ptr_not_null(s->data);

    int one = 1;
    int two = 2;
    int three = 3;
    stack_push(s, &one);
    stack_push(s, &two);
    munit_assert_int(s->capacity, ==, 2);
    munit_assert_int(s->count, ==, 2);
    
    stack_push(s, &three);
    munit_assert_int(s->capacity, ==, 4);
    munit_assert_int(s->count, ==, 3);

    int *popped = stack_pop(s);
    munit_assert_int(*popped, ==, three);
    popped = stack_pop(s);
    munit_assert_int(*popped, ==, two);
    popped = stack_pop(s);
    munit_assert_int(*popped, ==, one);
    popped = stack_pop(s);
    munit_assert_null(popped);

    stack_free(s);
    return MUNIT_OK;
}

static MunitResult
pop_stack_empty(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    stack_t *s = stack_new(2);
    assert_ptr_not_null(s);

    assert_int(s->capacity, ==, 2);
    assert_int(s->count, ==, 0);
    assert_ptr_not_null(s->data);

    int *popped = stack_pop(s);
    assert_null(popped);

    // Clean up our allocated data.
    stack_free(s);

    return MUNIT_OK;
}

static MunitResult
push_stack(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    stack_t *s = stack_new(2);
    assert_ptr_not_null(s);

    assert_int(s->capacity, ==, 2);
    assert_int(s->count, ==, 0);
    assert_ptr_not_null(s->data);

    int a = 1;

    stack_push(s, &a);
    stack_push(s, &a);

    assert_int(s->capacity, ==, 2);
    assert_int(s->count, ==, 2);

    stack_push(s, &a);
    assert_int(s->capacity, ==, 4);
    assert_int(s->count, ==, 3);

    // Clean up our allocated data.
    stack_free(s);

    return MUNIT_OK;
}

static MunitResult
create_stack(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    stack_t *s = stack_new(10);
    assert_int(s->capacity, ==, 10);
    assert_int(s->count, ==, 0);
    assert_ptr_not_null(s->data);

    // Clean up our allocated data.
    stack_free(s);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/create_stack", create_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/push_stack", push_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/pop_stack", pop_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/pop_stack_empty", pop_stack_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/stack-l4-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
