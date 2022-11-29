/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "files.h"
#include "history.h"

/*************************************************************/
/*                      DEFINE SECTION                       */
/*************************************************************/

#define CIN_VERSION     "v1.2.1"

#define ON      0x1u
#define CODE    0x2u
#define INCLUDE 0x4u
#define MACRO   0x8u

#define INCLUDE_STR      "#include"
#define INCLUDE_STR_SIZE 8
#define DEFINE_STR       "#define"
#define DEFINE_STR_SIZE  7

/*************************************************************/
/*                 LOCAL FUNCTION PROTOTYPES                 */
/*************************************************************/

void show_cin_info();
void show_prompt();
void handle_exit();
void clear_flags();

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

int main() {
    unsigned char status = ON;
    char buffer[MAX_STRING_SIZE];
    char *line;
    size_t len;
    size_t _x_;
    struct stat st = {0};
    int compile_status;

    if (stat("/tmp/cin", &st) == -1) {
        mkdir("/tmp/cin", 0700);
    }

    show_cin_info();

    _x_ = MAX_STRING_SIZE;
    line = buffer;
    init_history();
    while (status & ON) {
        show_prompt();
        len = getline(&line, &_x_, stdin);

        if (len > 2 && line[0] == ':' && line[1] == 'q') {
            status &= ~ON;
        } else {
            if (line[0] == '#') {
                if (!strncmp(INCLUDE_STR, line, INCLUDE_STR_SIZE)) {
                    push_include(line, len);
                    status |= INCLUDE;
                } else if (!strncmp(DEFINE_STR, line, DEFINE_STR_SIZE)) {
                    push_macro(line, len);
                    status |= MACRO;
                }
            } else {
                push_instruction(line, len);
                status |= CODE;
            }
            write_to_file();

            compile_status = compile_and_run();
            if (compile_status != 0) {
                if (status & CODE) {
                    pop_instruction();
                } else if (status & INCLUDE) {
                    pop_include();
                } else if (status & MACRO) {
                    pop_macro();
                }
            }

            clear_flags(&status);

            delete_files();
        }
    }

    handle_exit();

    return 0;
}

void show_cin_info() {
    printf("cin - %s", CIN_VERSION);
}

void show_prompt() {
    printf("\n>> ");
}

void handle_exit() {
    delete_dir();
}

void clear_flags(unsigned char *status) {
    *status &= ~CODE;
    *status &= ~INCLUDE;
    *status &= ~MACRO;
}
