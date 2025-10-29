#include <stdlib.h>
#include <string.h>

#include "snekobject.h"

bool snek_array_set(snek_object_t *snek_obj, size_t index, snek_object_t *value) {
    if (snek_obj == NULL || value == NULL) {
        return false;
    }
    if (snek_obj->kind != ARRAY) {
        return false;
    }
    // Size of n array's last element is index n-1
    if (index < 0 || index >= snek_obj->data.v_array.size) {
        return false;
    }
    snek_obj->data.v_array.elements[index] = value;
    return true;
}

snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t index) {
    if (snek_obj == NULL) {
        return NULL;
    }
    if (snek_obj->kind != ARRAY) {
        return NULL;
    }
    // Size of n array's last element is index n-1
    if (index < 0 || index >= snek_obj->data.v_array.size) {
        return false;
    }
    return snek_obj->data.v_array.elements[index];
}

// don't touch below this line

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  snek_object_t **elements = calloc(size, sizeof(snek_object_t *));
  if (elements == NULL) {
    free(obj);
    return NULL;
  }

  obj->kind = ARRAY;
  obj->data.v_array = (snek_array_t){.size = size, .elements = elements};
  return obj;
}

snek_object_t *new_snek_vector3(
    snek_object_t *x, snek_object_t *y, snek_object_t *z
) {
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }

  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = VECTOR3;
  obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};

  return obj;
}

snek_object_t *new_snek_integer(int value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = INTEGER;
  obj->data.v_int = value;
  return obj;
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = FLOAT;
  obj->data.v_float = value;
  return obj;
}

snek_object_t *new_snek_string(char *value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  int len = strlen(value);
  char *dst = malloc(len + 1);
  if (dst == NULL) {
    free(obj);
    return NULL;
  }

  strcpy(dst, value);

  obj->kind = STRING;
  obj->data.v_string = dst;
  return obj;
}

