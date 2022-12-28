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

/**
 * counter - number of added instructions
*/
static int counter;

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

void reset_counter() {
    counter = 0;
}

void push_instruction(char* buf, size_t len) {
    static history *tmp;
    tmp = malloc(sizeof(history));

    strcpy(tmp->buffer, buf);
    tmp->length = len;
    tmp->next = NULL;
    tmp->prev = last;
    
    last->next = tmp;
    last = tmp;
    counter++;
}

void pop_instruction() {
    while (counter != 0) {
        last = last->prev;

        free(last->next);
        last->next = NULL;
        counter--;
    }
}