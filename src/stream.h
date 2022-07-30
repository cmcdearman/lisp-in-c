#ifndef STREAM_H
#define STREAM_H

#include <stdlib.h>
#include "string.h"
#include <stdio.h>

// A Stream is an abstraction over files and strings for source input. It's 
// implemented as a consuming array of bytes that's only resizable in a
// constructor.
typedef struct
{
  String path;
  String src;
  size_t cur;
  size_t peek;
} Stream;

Stream *new_stream_from_path(String);
Stream *new_stream_from_string(String);
int stream_next(Stream *);
int stream_peek(Stream *);

#endif
