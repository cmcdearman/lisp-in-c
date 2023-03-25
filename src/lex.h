#ifndef LEX_H
#define LEX_H

#include "string.h"
#include "token.h"
#include <ctype.h>
#include <stdbool.h>


#define MAX_NUM_CHARS 32
#define MAX_IDENT_CHARS 255

TokenStream *lex(String);

#endif
