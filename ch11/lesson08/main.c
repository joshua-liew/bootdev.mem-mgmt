#define MUNIT_ENABLE_ASSERT_ALIASES
#include <stdio.h>
#include <stdlib.h>

#include "munit/munit.h"
#include "sneknew.h"
#include "vm.h"

static MunitResult
test_single_frame(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);

    snek_object_t *teej_skill = new_snek_integer(vm, 420);
    snek_object_t *lane_skill = new_snek_string(vm, "issues");

    mark(vm);
    // should not be marked because not in frame
    assert_false(teej_skill->is_marked);
    assert_false(lane_skill->is_marked);

    frame_reference_object(frame, teej_skill);
    frame_reference_object(frame, lane_skill);

    // after adding and marking, should be marked
    mark(vm);
    assert_true(teej_skill->is_marked);
    assert_true(lane_skill->is_marked);

    vm_free(vm);

    return MUNIT_OK;
}

static MunitResult
test_multi_frame(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);
    frame_t *frame2 = vm_new_frame(vm);

    snek_object_t *teej_skill = new_snek_integer(vm, 420);
    snek_object_t *lane_skill = new_snek_string(vm, "issues");
    snek_object_t *prime_skill = new_snek_string(vm, "infinite");

    frame_reference_object(frame, teej_skill);
    frame_reference_object(frame, lane_skill);
    frame_reference_object(frame2, prime_skill);
    mark(vm);

    assert_true(teej_skill->is_marked);
    assert_true(lane_skill->is_marked);
    assert_true(prime_skill->is_marked);
    vm_free(vm);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/test_single_frame", test_single_frame, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_multi_frame", test_multi_frame, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/marksweep-l8-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
