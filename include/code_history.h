#ifndef INSTRUCTION_HIST
#define INSTRUCTION_HIST

/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include "macros.h"
#include "history_struct.h"

#include <stddef.h>

/*************************************************************/
/*                     VARIABLE SECTION                      */
/*************************************************************/

extern history *start, *last;

/*************************************************************/
/*                    FUNCTION PROTOTYPES                    */
/*************************************************************/

void push_instruction(char* buf, size_t len);
void pop_instruction();
void reset_counter();

#endif