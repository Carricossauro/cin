#ifndef MACRO_HIST
#define MACRO_HIST

/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include "macros.h"

#include <stddef.h>

/*************************************************************/
/*                      TYPEDEF SECTION                      */
/*************************************************************/

typedef struct macro_history_t {
    char buffer[MAX_STRING_SIZE];
    size_t length;
    struct macro_history_t *next, *prev;
} macro_history;

/*************************************************************/
/*                     VARIABLE SECTION                      */
/*************************************************************/

extern macro_history *macro_start, *macro_last;

/*************************************************************/
/*                    FUNCTION PROTOTYPES                    */
/*************************************************************/

void push_macro(char* buf, size_t len);
void pop_macro();

#endif