#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(void* vp1, void* vp2, size_t size) {
    void* buff = malloc(size);
    memcpy(buff, vp1, size);
    memcpy(vp1, vp2, size);
    memcpy(vp2, buff, size);
    free(buff);
    return;
}
