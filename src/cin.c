#include <stdio.h>

#define CIN_VERSION "1.0v"
#define MAX_STRING_SIZE 256

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
    printf("cin - CLI interpreter for C");
    printf("\n");
    printf("%s", CIN_VERSION);
    printf("\n");
}

void show_prompt() {
    printf(">> ");
}

int main() {
    status running = ON;
    char localbuffer[MAX_STRING_SIZE];

    show_cin_info();

    while (running == ON) {
        show_prompt();
        scanf("%s", &localbuffer);
    }

    return 0;
}