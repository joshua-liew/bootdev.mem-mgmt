#include <stdio.h>
#include <stdlib.h>
#include "exercise.h"

void snek_zero_out(void* ptr, snek_object_kind_t kind) {
    if (ptr == NULL) {
        fprintf(stderr, "Exiting with code 1: parameter 'ptr' must not be NULL.");
        exit(1);
    }
    switch (kind) {
        case (INTEGER):
            ((snek_int_t*)ptr)->value = (int)0;
            return;
        case (FLOAT):
            ((snek_float_t*)ptr)->value = (float)0;
            return;
        case (BOOL):
            ((snek_float_t*)ptr)->value = (unsigned int)0;
            return;
        default:
            fprintf(stderr, "Exiting with code 1: unknown SnekObjectKind enum value.");
            exit(1);
    }
}
