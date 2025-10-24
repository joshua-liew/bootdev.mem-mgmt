#include <stdio.h>
#include <stdlib.h>
#include "exercise.h"

int main(void) {
    const int num_lists = 500;
    for (int i = 0; i < num_lists; i++) {
        int* lst = allocate_scalar_list(50000, 2);
        if (lst == NULL) {
            fprintf(stderr, "Failed to allocate list.\n");
            return 1;
        } else {
            printf("Allocated list %d\n", i);
        }
        free(lst);
        printf("Freed list %d\n", i);
    }
    return 0;
}
