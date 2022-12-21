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

        status = compare_regex(line);

        switch (status) {
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

        if (status == CODE || status == DEFINE || status == INCLUDE) {
            write_to_file();

            compile_status = compile_and_run();
            if (compile_status != 0) {
                if (status == CODE) {
                    pop_instruction();
                } else if (status == INCLUDE) {
                    pop_include();
                } else if (status == DEFINE) {
                    pop_define();
                }
            }

            delete_files();
        }
    }

    delete_dir();

    return 0;
}
