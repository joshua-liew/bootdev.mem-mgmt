#define MUNIT_ENABLE_ASSERT_ALIASES
#include <stdio.h>
#include <stdlib.h>

#include "munit/munit.h"
#include "sneknew.h"
#include "vm.h"

static MunitResult
test_one_ref(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);

    snek_object_t *lanes_wpm = new_snek_integer(vm, 9);
    frame_reference_object(frame, lanes_wpm);

    assert_int(frame->references->count, ==, 1);
    assert_ptr_equal(lanes_wpm, frame->references->data[0]);

    vm_free(vm);

    return MUNIT_OK;
}

static MunitResult
test_multi_ref(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);

    snek_object_t *lanes_wpm = new_snek_integer(vm, 9);
    snek_object_t *teej_wpm = new_snek_integer(vm, 160);
    frame_reference_object(frame, lanes_wpm);
    frame_reference_object(frame, teej_wpm);

    assert_int(frame->references->count, ==, 2);
    assert_ptr_equal(lanes_wpm, frame->references->data[0]);
    assert_ptr_equal(teej_wpm, frame->references->data[1]);

    vm_free(vm);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/test_one_ref", test_one_ref, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_multi_ref", test_multi_ref, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/marksweep-l6-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
