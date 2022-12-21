#ifndef INPUT
#define INPUT

/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include <stdbool.h>

/*************************************************************/
/*                      TYPEDEF SECTION                      */
/*************************************************************/

typedef enum {
    ON,
    CODE,
    INCLUDE,
    DEFINE,
    CLEAR,
    HELP,
    SHOW,
    WRONG_COMMAND,
    OFF
} status_t;

/*************************************************************/
/*                    FUNCTION PROTOTYPES                    */
/*************************************************************/

status_t compare_regex(char *line);

#endif // INPUT