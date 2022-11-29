#ifndef HISTORY
#define HISTORY

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

typedef struct macro_history_t {
    char buffer[MAX_STRING_SIZE];
    size_t length;
    struct macro_history_t *next, *prev;
} macro_history;

typedef struct include_history_t {
    char buffer[MAX_STRING_SIZE];
    size_t length;
    struct include_history_t *next, *prev;
} include_history;

/*************************************************************/
/*                     VARIABLE SECTION                      */
/*************************************************************/

extern code_history *start, *last;
extern macro_history *macro_start, *macro_last;
extern include_history *include_start, *include_last;

/*************************************************************/
/*                    FUNCTION PROTOTYPES                    */
/*************************************************************/

void push_instruction(char* buf, size_t len);
void push_include(char* buf, size_t len);
void push_macro(char* buf, size_t len);
void pop_instruction();
void pop_include();
void pop_macro();
void push_macro(char* buf, size_t len);
void init_history();

#endif // HISTORY