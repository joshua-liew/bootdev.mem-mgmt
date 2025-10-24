#include <stdio.h>
#include <stdlib.h>

#include "exercise.h"

int* allocate_scalar_array(int size, int multiplier) {
    int* ptr = malloc(size * sizeof(int));
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        *(ptr + i) = i * multiplier;
        // ptr[i] = i * multiplier;
    }

    return ptr;
}
