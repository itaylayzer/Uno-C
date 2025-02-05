#ifndef _INC_COMPUTE

#define _INC_COMPUTE

#include <stdbool.h>
#include <stdlib.h>

#include "../controller/types.h"

#define SCOREFN(func_name, body)                           \
    byte func_name(ubyte card, DBLIST hand, ubyte leading) \
    {                                                      \
        byte score = 0;                                    \
        body;                                              \
        return score;                                      \
    }
#define scoreadd score +=
#define SCOREFN_VARIABLE(var_name) byte (*var_name)(ubyte, DBLIST, ubyte)

DBLIST heauristic_alg(DBLIST array, ubyte leading);
ubyte prioritise_color(DBLIST hand);

#endif