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
#include "input.h"

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

        if (len > 1 && line[0] == ':') {
            if (compare_regex(line, EXIT_STR)) {
                status = OFF;
            } else if (compare_regex(NULL, SHOW_STR)) {
                write_to(1);
            }
        } else {
            if (compare_regex(line, INCLUDE_STR)) {
                push_include(line, len);
                status = INCLUDE;
            } else if (compare_regex(NULL, DEFINE_STR)) {
                push_macro(line, len);
                status = MACRO;
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
