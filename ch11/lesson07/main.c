#define MUNIT_ENABLE_ASSERT_ALIASES
#include <stdio.h>
#include <stdlib.h>

#include "munit/munit.h"
#include "sneknew.h"
#include "vm.h"

static MunitResult
test_field_exists(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    snek_object_t *lane_courses = new_snek_integer(vm, 20);
    snek_object_t *teej_courses = new_snek_integer(vm, 1);
    lane_courses->is_marked;
    teej_courses->is_marked;
    vm_free(vm);

    return MUNIT_OK;
}

static MunitResult
test_marked_is_false(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    snek_object_t *lane_courses = new_snek_integer(vm, 20);
    snek_object_t *teej_courses = new_snek_integer(vm, 1);
    assert_false(lane_courses->is_marked);
    assert_false(teej_courses->is_marked);
    vm_free(vm);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/test_field_exists", test_field_exists, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_marked_is_false", test_marked_is_false, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/marksweep-l7-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
