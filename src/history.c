/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include "history.h"

#include <string.h>
#include <stdlib.h>

/*************************************************************/
/*                      DEFINE SECTION                       */
/*************************************************************/


/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

void init_history() {
    start = malloc(sizeof(history));
    
    strcpy(start->buffer, MAIN_SIGNATURE);
    start->length = strlen(MAIN_SIGNATURE);
    last = start;
    last->prev = NULL;

    include_start = NULL;
    include_last = NULL;

    define_start = NULL;
    define_last = NULL;
}