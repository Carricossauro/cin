#include "history.h"

#include <string.h>
#include <stdlib.h>

#define MAIN_SIGNATURE  "int main(int argc, char**argv) {\n"

/**
 * start - beginning of code_history
 * last - second to last of code_history
*/
code_history *start, *last;

/**
 * macro_start - beginning of macro_history
 * macro_last - second to last of macro_history
*/
macro_history *macro_start, *macro_last;

/**
 * include_start - beginning of include_history
 * include_last - second to last of include_history
*/
include_history *include_start, *include_last;

void push_instruction(char* buf, size_t len) {
    static code_history *tmp;
    tmp = malloc(sizeof(code_history));

    strcpy(tmp->buffer, buf);
    tmp->length = len;
    tmp->next = NULL;
    tmp->prev = last;
    
    last->next = tmp;
    last = tmp;
}

void push_include(char* buf, size_t len) {
    static include_history *tmp;
    tmp = malloc(sizeof(include_history));

    strcpy(tmp->buffer, buf);
    tmp->length = len;
    tmp->next = NULL;
    tmp->prev = include_last;

    if (include_start == NULL) {
        include_start = tmp;
        include_last = tmp;
    } else {
        include_last->next = tmp;
        include_last = tmp;
    }
}

void pop_instruction() {
    last = last->prev;

    free(last->next);
    last->next = NULL;
}

void init_history() {
    start = malloc(sizeof(code_history));
    
    strcpy(start->buffer, MAIN_SIGNATURE);
    start->length = strlen(MAIN_SIGNATURE);
    last = start;
    last->prev = NULL;

    include_start = NULL;
    include_last = NULL;
}