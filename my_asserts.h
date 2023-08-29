#include <stdio.h>
#include <math.h>

#pragma once

/**
    * @file
    * Header with macros for my_assert
*/

#ifdef NDEBUG
    #define my_assert(expression, instructions) ;
#else
    /**
     * Used to find programmer's mistakes.
     * Accept expression, that should be checked and instructions, that should run.
     * Example: my_assert(c == NULL, printf("ERR"); return 0);
     * instead of (printf("ERR"); return 0) may be any other instructions
     */
    #define my_assert(expression, instructions) \
        if(!(expression)){ \
            fprintf(stderr, "ERROR IN FILE:%s FUNCTION:%s LINE:%d\n", __FILE__, __FUNCTION__, __LINE__); \
            instructions; \
        }
#endif // NDEBUG


