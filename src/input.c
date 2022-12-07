/*************************************************************/
/*                      INCLUDE SECTION                      */
/*************************************************************/

#include <regex.h>
#include <stddef.h>

#include "input.h"

/*************************************************************/
/*                   FUNCTION IMPLEMENTATION                 */
/*************************************************************/

bool compare_regex(char *line, char *pattern) {
    static regex_t string;
    static int regex_return = -1;

    regex_return = 0;
    if (line != NULL) {
        regex_return = regcomp(&string, line, 0);
    }
    
    regex_return += regexec(&string, pattern, 0, NULL, 0);

    return regex_return == 0;
}