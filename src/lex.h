#ifndef LEX_H
#define LEX_H

#include <stdbool.h>
#include "token.h"
#include <ctype.h>

#define MAX_NUM_CHARS 32
#define MAX_IDENT_CHARS 255

TokenStream *lex(char*);

#endif
