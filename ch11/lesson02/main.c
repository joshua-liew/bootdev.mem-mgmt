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
    assert_int(vm->frames->capacity, ==, 8);
    assert_int(vm->objects->capacity, ==, 8);
    vm_free(vm);

    return MUNIT_OK;
}

static MunitResult
test_vm_new_free(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    vm_free(vm);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/vm", test_vm_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/vm", test_vm_new_free, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/marksweep-l2-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
