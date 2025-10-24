#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exercise.h"

token_t** create_token_pointer_array(token_t* tokens, size_t count) {
    token_t** token_pointers = malloc(count * sizeof(token_t*));
    if (token_pointers == NULL) {
        fprintf(stderr, "Failed to allocate memory (token_pointers).\n");
        exit(1);
    }
    for (size_t i = 0; i < count; i++) {
        //token_pointers[i] = &tokens[i];
        token_t* ptr = (token_t*)malloc(sizeof(token_t));
        if (ptr == NULL) {
            fprintf(stderr, "Failed to allocate memory (ptr).\n");
            exit(1);
        }
        char* ptr_str = (char*)malloc(sizeof(tokens[i].literal));
        strcpy(ptr_str, tokens[i].literal);
        ptr->literal = ptr_str;
        //ptr->literal = (tokens + i)->literal;
        ptr->column = (tokens + i)->column;
        ptr->line = (tokens + i)->line;
        //ptr->literal = tokens[i].literal;
        //ptr->column = tokens[i].column;
        //ptr->line = tokens[i].line;
        token_pointers[i] = ptr;
    }
    return token_pointers;
}
