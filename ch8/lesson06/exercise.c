#include "snekstack.h"
#include <stdlib.h>
#include <string.h>

void stack_push_multiple_types(stack_t *s) {
    float *f = malloc(sizeof(float));
    if (f == NULL) {
        exit(1);
    }
    *f = 3.14;
    stack_push(s, f);

    char *ss = "Sneklang is blazingly slow!";
    char *hs = malloc((strlen(ss) + 1) * sizeof(char));
    if (hs == NULL) {
        free(f);
        exit(1);
    }
    strcpy(hs, ss);
    stack_push(s, hs);

    return;
}
