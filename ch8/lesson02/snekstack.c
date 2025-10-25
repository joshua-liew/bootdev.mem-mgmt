#include "snekstack.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void stack_push(stack_t* stack, void* obj) {
    if (stack->count == stack->capacity) {
        stack->capacity *= 2;
        stack->data = realloc(stack->data, (stack->capacity * sizeof(void *)));
        if (stack->data == NULL) {
            free(stack);
            fprintf(stderr, "Exiting with code 1: could not reallocate memory.");
            exit(1);
        }
    }

    *(stack->data + stack->count) = obj;
    //stack->data[stack->count] = obj;
    stack->count += 1;
    return;
}

stack_t* stack_new(size_t capacity) {
    stack_t* stack = malloc(sizeof(stack_t));
    if (stack == NULL) {
        return NULL;
    }

    stack->count = 0;
    stack->capacity = capacity;
    stack->data = malloc(stack->capacity * sizeof(void *));
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }
    return stack;
}
