#ifndef HISTORY_STRUCT
#define HISTORY_STRUCT

/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include <stddef.h>

/*************************************************************/
/*                      TYPEDEF SECTION                      */
/*************************************************************/

typedef struct history_t {
    char buffer[MAX_STRING_SIZE];
    size_t length;
    struct history_t *next, *prev;
} history;

#endif