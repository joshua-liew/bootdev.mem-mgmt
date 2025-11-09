#define MUNIT_ENABLE_ASSERT_ALIASES
#include <stdio.h>
#include <stdlib.h>

#include "munit/munit.h"
#include "sneknew.h"
#include "vm.h"

static MunitResult
test_simple(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    frame_t *f1 = vm_new_frame(vm);

    snek_object_t *s = new_snek_string(vm, "I wish I knew how to read.");
    frame_reference_object(f1, s);
    vm_collect_garbage(vm);
    // nothing should be collected because
    // we haven't freed the frame
    //assert(!boot_is_freed(s));

    frame_free(vm_frame_pop(vm));
    vm_collect_garbage(vm);
    //assert_true(boot_is_freed(s));

    vm_free(vm);

    return MUNIT_OK;
}

static MunitResult
test_full(const MunitParameter params[], void* data) {
    // Silence compiler warnings
    (void) params;
    (void) data;

    vm_t *vm = vm_new();
    frame_t *f1 = vm_new_frame(vm);
    frame_t *f2 = vm_new_frame(vm);
    frame_t *f3 = vm_new_frame(vm);

    snek_object_t *s1 = new_snek_string(vm, "This string is going into frame 1");
    frame_reference_object(f1, s1);

    snek_object_t *s2 = new_snek_string(vm, "This string is going into frame 2");
    frame_reference_object(f2, s2);

    snek_object_t *s3 = new_snek_string(vm, "This string is going into frame 3");
    frame_reference_object(f3, s3);

    snek_object_t *i1 = new_snek_integer(vm, 69);
    snek_object_t *i2 = new_snek_integer(vm, 420);
    snek_object_t *i3 = new_snek_integer(vm, 1337);
    snek_object_t *v = new_snek_vector3(
    vm,
    i1,
    i2,
    i3
    );
    frame_reference_object(f2, v);
    frame_reference_object(f3, v);

    assert_int(vm->objects->count, ==, 7);

    // only free the top frame (f3)
    frame_free(vm_frame_pop(vm));
    vm_collect_garbage(vm);
//    assert_true(boot_is_freed(s3));
//    assert_false(boot_is_freed(s1));
//    assert_false(boot_is_freed(s2));

    // VM pass should free the string, but not the vector
    // because its final frame hasn't been freed
    frame_free(vm_frame_pop(vm));
    frame_free(vm_frame_pop(vm));
    vm_collect_garbage(vm);
//    assert_true(boot_is_freed(s1));
//    assert_true(boot_is_freed(s2));
//    assert_true(boot_is_freed(s3));
//    assert_true(boot_is_freed(v));
//    assert_true(boot_is_freed(i1));
//    assert_true(boot_is_freed(i2));
//    assert_true(boot_is_freed(i3));

    assert_int(vm->objects->count, ==, 0);

    vm_free(vm);
    //assert_true(boot_all_freed());

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/test_simple", test_simple, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_full", test_full, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

int main(void) {
    static const MunitSuite suite = {
        "/marksweep-l10-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    return munit_suite_main(&suite, NULL, 0, NULL);
}
