#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "files.h"
#include "history.h"

#define CIN_VERSION     "v1.1.0"

/*************************************************************/
/*                      LOCAL TYPEDEFS                       */
/*************************************************************/

typedef enum {
    ON,
    OFF
} status;

/*************************************************************/
/*                 LOCAL FUNCTION PROTOTYPES                 */
/*************************************************************/

void show_cin_info();
void show_prompt();
void handle_exit();

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

void show_cin_info() {
    printf("cin - %s", CIN_VERSION);
}

void show_prompt() {
    printf("\n>> ");
}

void handle_exit() {
    delete_dir();
}

int main() {
    status running = ON;
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
    while (running == ON) {
        show_prompt();
        len = getline(&line, &_x_, stdin);

        if (len > 2 && line[0] == ':' && line[1] == 'q') {
            running = OFF;
        } else {
            if (line[0] == '#') {
                // ignore macro
            } else {
                push_instruction(line, len);
            }
            write_to_file();

            compile_status = compile_and_run();
            if (compile_status != 0) {
                pop_instruction();
            }

            delete_files();
        }
    }

    handle_exit();

    return 0;
}
