#include <stdio.h>
#include <stdlib.h>
#include "exercise.h"

char* get_full_greeting(char* greeting, char* name, int size) {
//    char full_greeting[100];
//    snprintf(full_greeting, 100, "%s %s", greeting, name);
//    return full_greeting;
    char* full_greeting = (char*)malloc(size * sizeof(char));
    if (full_greeting == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
//    printf("(size * sizeof(char)): %zu\n", size * sizeof(char));
//    printf("sizeof(full_greeting): %zu\n", sizeof(full_greeting));
//    printf("sizeof(char*): %zu\n", sizeof(char*));
    snprintf(full_greeting, (size * sizeof(char)), "%s %s", greeting, name);
    return full_greeting;
}
