/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>

#include "files.h"
#include "history.h"
#include "code_history.h"
#include "include_history.h"
#include "define_history.h"

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

void write_to_file() {
    static int file;
    file = open(FILENAME_C, O_WRONLY | O_CREAT, 0666);

    if (file > 0) {
        write_to(file);

        close(file);
    } else exit(errno);
}

void write_to(int wd) {
    history *it;

    it = include_start;
    while (it) {
        write(wd, it->buffer, it->length);
        write(wd, "\n", 1);

        it = it->next;
    }

    it = define_start;
    while (it) {
        write(wd, it->buffer, it->length);
        write(wd, "\n", 1);

        it = it->next;
    }

    it = start;
    while (it) {
        if (it != start) {
            write(wd, TAB, 4);
        }
        write(wd, it->buffer, it->length);
        write(wd, "\n", 1);

        it = it->next;
    }

    write(wd, "}\n", 2);
}

void delete_files() {
    remove(FILENAME_C);
    remove(OUTPUT);
}

void delete_dir() {
    remove("/tmp/cin");

    _exit(0);
}

int compile_and_run() {
    static int exec_status;
    static unsigned int output_history = 0;
    static unsigned int error_history = 0;
    static unsigned int i;
    static char c;
    int p[2];
    int perror[2];

    pipe(p);
    pipe(perror);

    exec_status = -1;

    if (fork() == 0) {
        close(perror[0]);
        dup2(perror[1], 2);
        close(perror[1]);
        int ret = execlp("gcc", "gcc", FILENAME_C, "-o", OUTPUT, (char*)NULL);

        _exit(ret);
    } else {
        close(perror[1]);

        (void)wait(&exec_status);
    }

    i = 0;
    while (read(perror[0], &c, 1)) {
        if (i >= error_history) {
            write(2, &c, 1);
        }

        i++;
    }

    if (!exec_status) {
        error_history = i;

        if (fork() == 0) {
            close(p[0]);
            dup2(p[1], 1);
            close(p[1]);

            int ret = execlp(OUTPUT, OUTPUT, (char*)NULL);

            _exit(ret);
        } else {
            close(p[1]);

           (void)wait(&exec_status);
        }
    }

    if (!exec_status) {
        i = 0;
        while (read(p[0], &c, 1)) {
            if (i >= output_history) {
                write(1, &c, 1);
            }

            i++;
        }
        if (i != output_history) {
            write(1, "\n", 1);
            output_history = i;
        }
    }


    close(p[0]);

    return exec_status;
}

void write_error(char *fmt, char *v) {
    char error_buffer[MAX_STRING_SIZE];
    int len;
    len = sprintf(error_buffer, fmt, v);

    write(2, "Error: ", 7);
    write(2, error_buffer, len);
    write(2, "\n", 1);
}