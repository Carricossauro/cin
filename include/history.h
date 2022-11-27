#ifndef HISTORY
#define HISTORY

#include "macros.h"

#include <stddef.h>

typedef struct history_t {
    char buffer[MAX_STRING_SIZE];
    size_t length;
    struct history_t *next, *prev;
} history;

extern history *start, *last;

void push_instruction(char* buf, size_t len);
void push_macro(char* buf, size_t len);

#endif // HISTORY