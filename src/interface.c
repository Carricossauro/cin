/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include <stdio.h>

#include "interface.h"
#include "macros.h"

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

void show_cin_info() {
    printf("cin - %s\n", CIN_VERSION);
}

void show_prompt() {
    printf(">> ");
}

size_t receive_input(char *line) {
    size_t _x_ = MAX_STRING_SIZE;

    return getline(&line, &_x_, stdin);
}