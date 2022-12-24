/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include <stdio.h>

#include "interface.h"
#include "files.h"
#include "macros.h"
#include "history.h"

/*************************************************************/
/*                      DEFINE SECTION                       */
/*************************************************************/

#define FLAG_STRING          0x1u
#define FLAG_CHAR            0x2u
#define FLAG_CURLY_BRACKETS  0x4u

#define STRING_QUOTES        '"'
#define CHAR_QUOTES          '\''
#define SEMICOLON            ';'

#define CURLY_BRACKETS_OPEN  '{'
#define CURLY_BRACKETS_CLOSE '}'

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
    static char *it;
    static char *startLine;
    static unsigned char flags;

    len = getline(&line, &_x_, stdin);
    len--;
    line[len] = 0;

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
            write_error("command %s not recognized", &line[1]);
            break;
        case DEFINE:
            push_define(line, len);
            break;
        case INCLUDE:
            push_include(line, len);
            break;
        case CODE:
            startLine = line;
            flags = 0u;
            for (it = line, len = 0; *it; it++, len++) {
                if (*it == CHAR_QUOTES) {
                    if (flags & FLAG_CHAR && *(it - 1) != '\\') {
                        flags &= ~FLAG_CHAR;
                    } else {
                        flags |= FLAG_CHAR;
                    }
                } else if (*it == STRING_QUOTES) {
                    if (flags & FLAG_STRING && *(it - 1) != '\\') {
                        flags &= ~FLAG_STRING;
                    } else {
                        flags |= FLAG_STRING;
                    }
                } else if (*it == SEMICOLON) {
                    if (!(flags & FLAG_CHAR) && !(flags & FLAG_STRING)) {
                        startLine[len + 1] = 0;
                        push_instruction(startLine, len + 1);

                        flags = 0u;
                        len = -1;

                        it++;
                        startLine = it + 1;
                    }
                }
            }

            break;
    }
}