#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "files.h"
#include "history.h"

#define CIN_VERSION     "1.0v"
#define MAIN_SIGNATURE  "int main(int argc, char**argv) {\n"

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
void push_instruction(char* buf, size_t len);
void push_macro(char* buf, size_t len);

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
    strcpy(start->buffer, MAIN_SIGNATURE);
    start->length = strlen(MAIN_SIGNATURE);
    last = start;
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

void push_instruction(char* buf, size_t len) {
    static history *tmp;
    tmp = malloc(sizeof(history));

    strcpy(tmp->buffer, buf);
    tmp->length = len;
    tmp->next = NULL;
    
    last->next = tmp;
    last = tmp;
}

void push_macro(char* buf, size_t len) {
    static history *tmp;
    tmp = malloc(sizeof(history));

    strcpy(tmp->buffer, buf);
    tmp->length = len;
    tmp->next = NULL;

    if (!strncmp("#include", buf, 8)) {
        tmp->next = start;
        start = tmp;
    } else {
        history *it = start;
        history *prev = NULL;
        while (strncmp("int main", it->buffer, 8)) {
            prev = it;
            it = it->next;
        }

        tmp->next = it;
        if (prev == NULL) {
            start = tmp;
        } else {
            prev->next = tmp;
        }
    }
}
