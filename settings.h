#ifndef pw_gen
#include "pw_gen.h"
#endif

#define MAX_LEN 12
#define NUM_UPPER_CASE 1            // at least: 1 
#define NUM_SPEC_CHARS 1            // at least: 1 
#define NUM_DIGITS 2                // at least: 1
#define ALLOWED_DUP_CHAR 2

const char SPECIAL_CHARS[] = "@";    // ex: "!@#$%^&*"
const char AMBIGUOUS_CHARS[] = "O0Il1SA";