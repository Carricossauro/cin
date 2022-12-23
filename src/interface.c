/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include <stdio.h>

#include "interface.h"
#include "files.h"
#include "macros.h"
#include "history.h"

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

void write_error(char *fmt, char *v) {
    printf("Error: ");
    printf(fmt, v);
    putchar('\n');
}

void clear_screen() {
    printf("\e[1;1H\e[2J");
}

void receive_input(char *line, status_t *status) {
    size_t _x_ = MAX_STRING_SIZE;
    static int len;

    len = getline(&line, &_x_, stdin);

    *status = compare_regex(line);

    switch (*status) {
        case SHOW:
            write_to(1);
            break;
        case CLEAR:
            clear_screen();
            break;
        case HELP:
            write_help();
            break;
        case WRONG_COMMAND:
            line[len - 1] = 0;
            write_error("command %s not recognized", &line[1]);
            break;
        case INCLUDE:
            push_include(line, len);
            break;
        case DEFINE:
            push_define(line, len);
            break;
        case CODE:
            push_instruction(line, len);
            break;
    }
}