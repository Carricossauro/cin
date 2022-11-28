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
*/
macro_history *macro_start, *macro_last;

void push_instruction(char* buf, size_t len) {
    static code_history *tmp;
    tmp = malloc(sizeof(code_history));

    strcpy(tmp->buffer, buf);
    tmp->length = len;
    tmp->next = NULL;
    
    last->next = tmp;
    last = tmp;
}

void push_macro(char* buf, size_t len) {
    static macro_history *tmp;
    tmp = malloc(sizeof(macro_history));

    strcpy(tmp->buffer, buf);
    tmp->length = len;
    tmp->next = NULL;

    if (macro_last == NULL) {
        macro_last = tmp;
    }

    if (!strncmp("#include", buf, 8)) {
        tmp->next = macro_start;
        macro_start = tmp;
    } else {
        if (macro_start == NULL) {
            macro_start = tmp;
        } else {
            macro_history *it;

            it = macro_start;
            while (it->next != NULL) {
                it = it->next;
            }

            it->next = tmp;
            macro_last = tmp;
        }
    }
}

void init_history() {
    start = malloc(sizeof(code_history));
    macro_start = NULL;
    macro_last = NULL;
    
    strcpy(start->buffer, MAIN_SIGNATURE);
    start->length = strlen(MAIN_SIGNATURE);
    last = start;
}