#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "files.h"
#include "history.h"

#define CIN_VERSION     "v1.0.0"

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

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

void show_cin_info() {
    printf("cin - %s", CIN_VERSION);
}

void show_prompt() {
    printf("\n>> ");
}

int main() {
    status running = ON;
    char buffer[MAX_STRING_SIZE];
    char *line;
    size_t len;
    size_t _x_;
    struct stat st = {0};

    if (stat("/tmp/cin", &st) == -1) {
        mkdir("/tmp/cin", 0700);
    }

    show_cin_info();

    start = malloc(sizeof(history));

    _x_ = MAX_STRING_SIZE;
    line = buffer;
    while (running == ON) {
        show_prompt();
        len = getline(&line, &_x_, stdin);

        if (len > 2 && line[0] == ':' && line[1] == 'q') {
            running = OFF;
        } else {
            if (line[0] == '#') {
                push_macro(line, len);
            } else {
                push_instruction(line, len);
            }
            write_to_file();

            compile_and_run();

            delete_files();
        }
    }

    return 0;
}
