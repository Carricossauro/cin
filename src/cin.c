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
        receive_input(line, &status);

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
