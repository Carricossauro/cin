#ifndef INTERFACE
#define INTERFACE

/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include "input.h"

/*************************************************************/
/*                    FUNCTION PROTOTYPES                    */
/*************************************************************/

void show_cin_info();
void show_prompt();
void write_help();
void clear_screen();
void write_error(char *fmt, char *v);
void receive_input(char *line, status_t *status);

#endif