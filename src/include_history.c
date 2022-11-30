/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include "include_history.h"

#include <string.h>
#include <stdlib.h>

/*************************************************************/
/*                     GLOBAL VARIABLES                      */
/*************************************************************/

/**
 * include_start - beginning of include_history
 * include_last - second to last of include_history
*/
include_history *include_start, *include_last;

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

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