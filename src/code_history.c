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
 * start - beginning of code_history
 * last - second to last of code_history
*/
code_history *start, *last;

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

void pop_instruction() {
    last = last->prev;

    free(last->next);
    last->next = NULL;
}