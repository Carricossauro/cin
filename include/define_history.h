#ifndef DEFINE_HIST
#define DEFINE_HIST

/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include "macros.h"
#include "history_struct.h"

#include <stddef.h>

/*************************************************************/
/*                     VARIABLE SECTION                      */
/*************************************************************/

extern history *define_start, *define_last;

/*************************************************************/
/*                    FUNCTION PROTOTYPES                    */
/*************************************************************/

void push_define(char* buf, size_t len);
void pop_define();

#endif