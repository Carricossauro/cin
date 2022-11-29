#ifndef HISTORY
#define HISTORY

#include "macros.h"

#include <stddef.h>

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

extern code_history *start, *last;
extern macro_history *macro_start, *macro_last;
extern include_history *include_start, *include_last;

void push_instruction(char* buf, size_t len);
void pop_instruction();
void push_macro(char* buf, size_t len);
void init_history();

#endif // HISTORY