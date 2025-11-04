#define MUNIT_ENABLE_ASSERT_ALIASES
#include <stdio.h>
#include <stdlib.h>

#include "munit/munit.h"
#include "snekobject.h"
#include "vm.h"

static MunitResult
test_vm_new(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    vm_new_frame(vm);
    assert_int(vm->frames->count, ==, 1);
    vm_free(vm);

    return MUNIT_OK;
}

static MunitResult
test_vm_new_frame(const MunitParameter params[], void *data) {
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);
    assert_ptr(frame->references, !=, NULL);
    assert_int(frame->references->count, ==, 0);
    assert(frame->references->capacity > 0); // references stack must have capacity > 0
    assert_ptr(frame->references->data, !=, NULL);
    vm_free(vm);

    return MUNIT_OK;
}

static MunitResult
test_frames_are_freed(const MunitParameter params[], void *data) {
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    vm_new_frame(vm);
    vm_free(vm);
    //assert(boot_all_freed());

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/test_vm_new", test_vm_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_vm_new_frame", test_vm_new_frame, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_frames_are_freed", test_frames_are_freed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/marksweep-l3-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
