#include "snekstack.h"
#include "stdlib.h"

void scary_double_push(stack_t *s) {
    stack_push(s, (void *)1337);
    int *i = malloc(sizeof(int));
    *i = 1024;
    stack_push(s, i);
}
