#ifndef STREAM_H
#define STREAM_H

#include <stdlib.h>
#include "string.h"
#include <stdio.h>

// A Stream is an abstraction over files and strings for source input
typedef struct {
	char* path;
	String* src;	
	size_t pos;
} Stream;

Stream* new_stream_from_path(char*);
Stream* new_stream_from_string(String*);
char stream_next(Stream*);

#endif
