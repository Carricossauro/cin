#ifndef INTERFACE
#define INTERFACE

/*************************************************************/
/*                    FUNCTION PROTOTYPES                    */
/*************************************************************/

void show_cin_info();
void show_prompt();
void write_help();
void clear_screen();
void write_error(char *fmt, char *v);
size_t receive_input(char *line);

#endif