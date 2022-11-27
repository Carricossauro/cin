#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>

#include "files.h"
#include "history.h"

void write_to_file() {
    static int file;
    file = open(FILENAME_C, O_WRONLY | O_CREAT, 0666);

    if (file > 0) {
        history *it;

        it = start;
        while (it) {
            write(file, it->buffer, it->length);

            it = it->next;
        }

        write(file, "}\n", 2);

        close(file);
    } else exit(errno);
}

void delete_files() {
    remove(FILENAME_C);
    remove(OUTPUT);
}

int compile_and_run() {
    static int exec_status;

    exec_status = -1;

    if (fork() == 0) {
        int ret = execlp("gcc", "gcc", FILENAME_C, "-o", OUTPUT, (char*)NULL);

        _exit(ret);
    } else {
        (void)wait(&exec_status);
    }

    if (!exec_status) {
        if (fork() == 0) {
            int ret = execlp(OUTPUT, OUTPUT, (char*)NULL);

            _exit(ret);
        } else {
           (void)wait(&exec_status);
        }
    }

    return exec_status;
}