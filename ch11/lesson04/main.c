#define MUNIT_ENABLE_ASSERT_ALIASES
#include <stdio.h>
#include <stdlib.h>

#include "munit/munit.h"
#include "snekobject.h"
#include "sneknew.h"
#include "vm.h"

static MunitResult
test_new_object(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    snek_object_t *obj = new_snek_integer(vm, 5);
    assert_int(obj->kind, ==, INTEGER);
    assert_ptr_equal(vm->objects->data[0], obj);
    free(obj);
    vm_free(vm);
    //assert(boot_all_freed());

    return MUNIT_OK;
}

static MunitResult
test_vm_new(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    assert_ptr_not_null(vm->frames);
    assert_ptr_not_null(vm->objects);
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
    vm_free(vm);
    //assert(boot_all_freed());

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/test_vm_new", test_vm_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_new_object", test_new_object, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_frames_are_freed", test_frames_are_freed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/marksweep-l4-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
