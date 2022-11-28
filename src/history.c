#include "history.h"

#include <string.h>
#include <stdlib.h>

#define MAIN_SIGNATURE  "int main(int argc, char**argv) {\n"

/**
 * start - beginning of code_history
 * last - second to last of code_history
*/
code_history *start, *last;

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
    static code_history *tmp;
    tmp = malloc(sizeof(code_history));

    strcpy(tmp->buffer, buf);
    tmp->length = len;
    tmp->next = NULL;

    if (!strncmp("#include", buf, 8)) {
        tmp->next = start;
        start = tmp;
    } else {
        code_history *it = start;
        code_history *prev = NULL;
        while (strncmp("int main", it->buffer, 8)) {
            prev = it;
            it = it->next;
        }

        tmp->next = it;
        if (prev == NULL) {
            start = tmp;
        } else {
            prev->next = tmp;
        }
    }
}

void init_history() {
    start = malloc(sizeof(code_history));
    
    strcpy(start->buffer, MAIN_SIGNATURE);
    start->length = strlen(MAIN_SIGNATURE);
    last = start;
}