/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include "history.h"

#include <string.h>
#include <stdlib.h>

/*************************************************************/
/*                      DEFINE SECTION                       */
/*************************************************************/

#define MAIN_SIGNATURE  "int main(int argc, char**argv) {\n"

/*************************************************************/
/*                     LOCAL VARIABLES                       */
/*************************************************************/

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

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

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

void pop_include() {
    if (include_last == include_start) {
        free(include_start);
        include_start = NULL;
        include_last = NULL;
    } else {
        include_last = include_last->prev;

        free(include_last->next);
        include_last->next = NULL;
    }
}

void push_macro(char* buf, size_t len) {
    static macro_history *tmp;
    tmp = malloc(sizeof(macro_history));

    strcpy(tmp->buffer, buf);
    tmp->length = len;
    tmp->next = NULL;
    tmp->prev = macro_last;

    if (macro_start == NULL) {
        macro_start = tmp;
        macro_last = tmp;
    } else {
        macro_last->next = tmp;
        macro_last = tmp;
    }
}

void pop_macro() {
    if (macro_last == macro_start) {
        free(macro_start);
        macro_start = NULL;
        macro_last = NULL;
    } else {
        macro_last = macro_last->prev;

        free(macro_last->next);
        macro_last->next = NULL;
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