/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include <regex.h>

#include "input.h"

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

bool compare_regex(char *line, char *pattern) {
    static regex_t string;
    static char *previous_line = NULL;
    static int regex_return = -1;

    if (line != previous_line) {
        previous_line = line;

        regex_return = regcomp(&string, line, 0);

        if (regex_return == 0) {
            regex_return = regexec(&string, pattern, 0, NULL, 0);
        }
    }

    return regex_return == 0;
}