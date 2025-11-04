#define MUNIT_ENABLE_ASSERT_ALIASES
#include <stdio.h>
#include <stdlib.h>

#include "munit/munit.h"
#include "snekobject.h"

static MunitResult
correctly_free(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    snek_object_t *first = new_snek_array(1);
    snek_object_t *second = new_snek_array(1);
    // refcounts: first = 1, second = 1
    snek_array_set(first, 0, second);
    // refcounts: first = 1, second = 2
    snek_array_set(second, 0, first);
    // refcounts: first = 2, second = 2
    refcount_dec(first);
    refcount_dec(second);
    assert_int(first->refcount, ==, 1);
    assert_int(second->refcount, ==, 1);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/correctly_free", correctly_free, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/marksweep-l1-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
