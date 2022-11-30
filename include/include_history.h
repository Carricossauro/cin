#ifndef INCLUDE_HIST
#define INCLUDE_HIST

/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include "macros.h"
#include "history_struct.h"

#include <stddef.h>

/*************************************************************/
/*                     VARIABLE SECTION                      */
/*************************************************************/

extern history *include_start, *include_last;

/*************************************************************/
/*                    FUNCTION PROTOTYPES                    */
/*************************************************************/

void push_include(char* buf, size_t len);
void pop_include();

#endif