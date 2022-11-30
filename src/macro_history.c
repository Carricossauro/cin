/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include "macro_history.h"

#include <string.h>
#include <stdlib.h>

/*************************************************************/
/*                     GLOBAL VARIABLES                      */
/*************************************************************/

/**
 * macro_start - beginning of macro history
 * macro_last - second to last of macro history
*/
history *macro_start, *macro_last;

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

void push_macro(char* buf, size_t len) {
    static history *tmp;
    tmp = malloc(sizeof(history));

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