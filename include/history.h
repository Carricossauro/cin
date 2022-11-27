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

#endif // HISTORY