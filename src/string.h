#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <string.h>

// A String is a dynamically sized char array
typedef struct {
	char* str;
	size_t len;
	size_t size;
} String;

#endif
