#ifndef HISTORY
#define HISTORY

#include "macros.h"

#include <stddef.h>

typedef struct code_history_t {
    char buffer[MAX_STRING_SIZE];
    size_t length;
    struct code_history_t *next, *prev;
} code_history;

extern code_history *start, *last;

typedef struct macro_history_t {
    char buffer[MAX_STRING_SIZE];
    size_t length;
    struct macro_history_t *next;
} macro_history;

extern macro_history *start;

void push_instruction(char* buf, size_t len);
void push_macro(char* buf, size_t len);
void init_history();

#endif // HISTORY