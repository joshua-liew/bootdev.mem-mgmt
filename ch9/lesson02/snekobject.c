#include <stdlib.h>

#include "snekobject.h"

snek_object_t *new_snek_integer(int value) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) {
        exit(1);
    }
    obj->kind = INTEGER;
    obj->data.v_int = value;
    return obj;
}
