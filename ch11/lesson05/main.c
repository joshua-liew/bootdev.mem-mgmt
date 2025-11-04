#include <stdio.h>
#include <stdlib.h>

#include "munit/munit.h"
#include "sneknew.h"
#include "vm.h"

static MunitResult
test_reference_object(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    new_snek_integer(vm, 5);
    new_snek_string(vm, "hello");
    vm_free(vm);
    //assert(boot_all_freed());

    return MUNIT_OK;
}

static MunitResult
test_frames_are_freed(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    vm_new_frame(vm);
    vm_new_frame(vm);
    vm_free(vm);
    //assert(boot_all_freed());

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/test_reference_object", test_reference_object, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_frames_are_freed", test_frames_are_freed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/marksweep-l5-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
