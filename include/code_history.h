#ifndef INSTRUCTION_HIST
#define INSTRUCTION_HIST

/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include "macros.h"

#include <stddef.h>

/*************************************************************/
/*                      TYPEDEF SECTION                      */
/*************************************************************/

typedef struct code_history_t {
    char buffer[MAX_STRING_SIZE];
    size_t length;
    struct code_history_t *next, *prev;
} code_history;

/*************************************************************/
/*                     VARIABLE SECTION                      */
/*************************************************************/

extern code_history *start, *last;

/*************************************************************/
/*                    FUNCTION PROTOTYPES                    */
/*************************************************************/

void push_instruction(char* buf, size_t len);
void pop_instruction();

#endif