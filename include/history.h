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

void push_instruction(char* buf, size_t len);
void pop_instruction();
void push_macro(char* buf, size_t len);
void init_history();

#endif // HISTORY