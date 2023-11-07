#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A String is an immutable character array
typedef char *String;

String string_from_file(String);
String string_cat(String, String);

#endif
