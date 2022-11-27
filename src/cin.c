#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
#include <sys/stat.h>

#define CIN_VERSION     "1.0v"
#define MAX_STRING_SIZE 512
#define FILENAME_C      "/tmp/cin/tmp_code.c"
#define OUTPUT          "/tmp/cin/out.app"
#define MAIN_SIGNATURE  "int main(int argc, char**argv) {\n"

/*************************************************************/
/*                      LOCAL TYPEDEFS                       */
/*************************************************************/

typedef enum {
    ON,
    OFF
} status;

typedef struct history_t {
    char buffer[MAX_STRING_SIZE];
    size_t length;
    struct history_t *next;
} history;

/*************************************************************/
/*                      LOCAL VARIABLES                      */
/*************************************************************/

/**
 * start - beginning of code history
 * slast - second to last of code history
*/
history *start, *slast;

/*************************************************************/
/*                 LOCAL FUNCTION PROTOTYPES                 */
/*************************************************************/

void show_cin_info();
void show_prompt();
void push_instruction(char* buf, size_t len);
void write_to_file();
void delete_file();
int compile_and_run();

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

void show_cin_info() {
    printf("cin - CLI interpreter for C");
    printf("\n");
    printf("%s", CIN_VERSION);
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
    strcpy(start->buffer, MAIN_SIGNATURE);
    start->length = strlen(MAIN_SIGNATURE);
    slast = NULL;
    while (running == ON) {
        show_prompt();
        len = getline(&line, &_x_, stdin);

        if (len > 2 && line[0] == ':' && line[1] == 'q') {
            running = OFF;
        } else {
            push_instruction(line, len);
            write_to_file();

            compile_and_run();

            delete_file();
        }
    }

    return 0;
}

void push_instruction(char* buf, size_t len) {
    static history *tmp;
    tmp = malloc(sizeof(history));

    strcpy(tmp->buffer, buf);
    tmp->length = len;
    tmp->next = NULL;
    
    if (slast == NULL) {
        slast = start;
    } else {
        slast = slast->next;
    }
    slast->next = tmp;
}

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

void delete_file() {
    remove(FILENAME_C);
}

int compile_and_run() {
    int exec_status;

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