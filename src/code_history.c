/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include "code_history.h"

#include <string.h>
#include <stdlib.h>

/*************************************************************/
/*                     GLOBAL VARIABLES                      */
/*************************************************************/

/**
 * start - beginning of code history
 * last - second to last of code history
*/
history *start, *last;

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

void push_instruction(char* buf, size_t len) {
    static history *tmp;
    tmp = malloc(sizeof(history));

    strcpy(tmp->buffer, buf);
    tmp->length = len;
    tmp->next = NULL;
    tmp->prev = last;
    
    last->next = tmp;
    last = tmp;
}

void pop_instruction() {
    last = last->prev;

    free(last->next);
    last->next = NULL;
}