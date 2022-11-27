#include "history.h"

#include <string.h>
#include <stdlib.h>

/**
 * start - beginning of code history
 * last - second to last of code history
*/
history *start, *last;

void push_instruction(char* buf, size_t len) {
    static history *tmp;
    tmp = malloc(sizeof(history));

    strcpy(tmp->buffer, buf);
    tmp->length = len;
    tmp->next = NULL;
    
    last->next = tmp;
    last = tmp;
}

void push_macro(char* buf, size_t len) {
    static history *tmp;
    tmp = malloc(sizeof(history));

    strcpy(tmp->buffer, buf);
    tmp->length = len;
    tmp->next = NULL;

    if (!strncmp("#include", buf, 8)) {
        tmp->next = start;
        start = tmp;
    } else {
        history *it = start;
        history *prev = NULL;
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