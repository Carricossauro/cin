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
    printf("Type :help for additional information\n");
}

void show_prompt() {
    printf(">> ");
}

void write_help() {
    printf("Copyright (C) 2022 Tiago Carriço\n");
    printf("MIT License\n\n");
    printf("Commands:\n");
    printf("    - help: displays this help menu\n");
    printf("    - show: displays current code in storage\n");
    printf("    - exit: exits cin\n");
}

size_t receive_input(char *line) {
    size_t _x_ = MAX_STRING_SIZE;

    return getline(&line, &_x_, stdin);
}