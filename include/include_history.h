#ifndef INCLUDE_HIST
#define INCLUDE_HIST

/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include "macros.h"

#include <stddef.h>

/*************************************************************/
/*                      TYPEDEF SECTION                      */
/*************************************************************/

typedef struct include_history_t {
    char buffer[MAX_STRING_SIZE];
    size_t length;
    struct include_history_t *next, *prev;
} include_history;

/*************************************************************/
/*                     VARIABLE SECTION                      */
/*************************************************************/

extern include_history *include_start, *include_last;

/*************************************************************/
/*                    FUNCTION PROTOTYPES                    */
/*************************************************************/

void push_include(char* buf, size_t len);
void pop_include();

#endif