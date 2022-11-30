#ifndef MACRO_HIST
#define MACRO_HIST

/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include "macros.h"
#include "history_struct.h"

#include <stddef.h>

/*************************************************************/
/*                     VARIABLE SECTION                      */
/*************************************************************/

extern history *macro_start, *macro_last;

/*************************************************************/
/*                    FUNCTION PROTOTYPES                    */
/*************************************************************/

void push_macro(char* buf, size_t len);
void pop_macro();

#endif