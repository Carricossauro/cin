/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include "define_history.h"

#include <string.h>
#include <stdlib.h>

/*************************************************************/
/*                     GLOBAL VARIABLES                      */
/*************************************************************/

/**
 * define_start - beginning of define history
 * define_last - second to last of define history
*/
history *define_start, *define_last;

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

void push_define(char* buf, size_t len) {
    static history *tmp;
    tmp = malloc(sizeof(history));

    strcpy(tmp->buffer, buf);
    tmp->length = len;
    tmp->next = NULL;
    tmp->prev = define_last;

    if (define_start == NULL) {
        define_start = tmp;
        define_last = tmp;
    } else {
        define_last->next = tmp;
        define_last = tmp;
    }
}

void pop_define() {
    if (define_last == define_start) {
        free(define_start);
        define_start = NULL;
        define_last = NULL;
    } else {
        define_last = define_last->prev;

        free(define_last->next);
        define_last->next = NULL;
    }
}