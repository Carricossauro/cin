/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>

#include "interface.h"
#include "files.h"
#include "history.h"

/*************************************************************/
/*                      TYPEDEF SECTION                      */
/*************************************************************/

typedef enum {
    ON,
    CODE,
    INCLUDE,
    MACRO,
    OFF
} status_t;

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

int main() {
    status_t status = ON;
    char buffer[MAX_STRING_SIZE];
    char *line;
    size_t len;
    struct stat st = {0};
    int compile_status;

    signal(SIGTERM, delete_dir);
    signal(SIGINT, delete_dir);
    signal(SIGQUIT, delete_dir);
    signal(SIGHUP, delete_dir);

    if (stat(DIRECTORY, &st) == -1) {
        mkdir(DIRECTORY, 0700);
    }

    show_cin_info();

    line = buffer;
    init_history();
    while (status != OFF) {
        show_prompt();
        len = receive_input(line);

        if (len > 2 && line[0] == ':' && line[1] == 'q') {
            status = OFF;
        } else {
            if (line[0] == '#') {
                if (!strncmp(INCLUDE_STR, line, INCLUDE_STR_SIZE)) {
                    push_include(line, len);
                    status = INCLUDE;
                } else if (!strncmp(DEFINE_STR, line, DEFINE_STR_SIZE)) {
                    push_macro(line, len);
                    status = MACRO;
                }
            } else {
                push_instruction(line, len);
                status = CODE;
            }
            write_to_file();

            compile_status = compile_and_run();
            if (compile_status != 0) {
                if (status == CODE) {
                    pop_instruction();
                } else if (status == INCLUDE) {
                    pop_include();
                } else if (status == MACRO) {
                    pop_macro();
                }
            }

            delete_files();
        }
    }

    delete_dir();

    return 0;
}
