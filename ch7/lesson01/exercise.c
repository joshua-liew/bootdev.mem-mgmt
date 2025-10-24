#include "stdlib.h"

#include "exercise.h"

void allocate_int(int** pointer_pointer, int value) {
    int* ptr = (int*)malloc(sizeof(int));
    if (ptr == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    *pointer_pointer = ptr;
    *ptr = value;
    // **pointer_pointer = value;
    return;
}
