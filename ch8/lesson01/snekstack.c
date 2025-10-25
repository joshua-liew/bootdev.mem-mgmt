#include "snekstack.h"
#include <stdlib.h>
#include <stdio.h>

stack_t* stack_new(size_t capacity) {
    stack_t* stk = (stack_t*)malloc(sizeof(stack_t));
    if (stk == NULL) {
        fprintf(stderr, "Exiting with code 1: could not allocate memory. (stk)");
        exit(1);
    }

    stk->count = 0;
    stk->capacity = capacity;
    void** stk_data = (void**)malloc(capacity * sizeof(void*));
    if (stk_data == NULL) {
        fprintf(stderr, "Exiting with code 1: could not allocate memory. (stk_data)");
        exit(1);
    }
    stk->data = stk_data;
    return stk;
}
