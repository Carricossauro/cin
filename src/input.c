/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include <regex.h>
#include <stddef.h>

#include "input.h"
#include "macros.h"

/*************************************************************/
/*                      DEFINE SECTION                       */
/*************************************************************/

#define EXIT_STR         ":exit"
#define CLEAR_STR        ":clear"
#define HELP_STR         ":help"
#define SHOW_STR         ":show"
#define COMMAND_STR      ":.*"
#define INCLUDE_STR      "#include.*"
#define DEFINE_STR       "#define.*"

#define REGEX_STRINGS 7

/*************************************************************/
/*                      TYPEDEF SECTION                      */
/*************************************************************/

typedef struct {
    char string[MAX_STRING_SIZE];
    status_t status;
} regex_string_t;

/*************************************************************/
/*                   LOCAL VARIABLES SECTION                 */
/*************************************************************/

regex_string_t regex_string[REGEX_STRINGS] = {
    {EXIT_STR    , OFF           },
    {CLEAR_STR   , CLEAR         },
    {HELP_STR    , HELP          },
    {SHOW_STR    , SHOW          },
    {COMMAND_STR , WRONG_COMMAND },
    {INCLUDE_STR , INCLUDE       },
    {DEFINE_STR  , DEFINE        }
};

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

status_t compare_regex(char *line) {
    static regex_t string;
    static int regex_return = -1;
    static status_t regex_status;
    static int i;

    regex_status = ON;
    if (line != NULL) {
        regex_status = CODE;

        for (i = 0; i < REGEX_STRINGS && regex_status == CODE; i++) {
            regex_return = regcomp(&string, regex_string[i].string, 0);

            regex_return += regexec(&string, line, 0, NULL, 0);

            if (regex_return == 0) {
                regex_status = regex_string[i].status;
            }
        }

    }

    return regex_status;
}