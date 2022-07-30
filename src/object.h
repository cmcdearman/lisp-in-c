#ifndef OBJECT_H
#define OBJECT_H

#include "string.h"

struct Object;

typedef struct Object {
  union {
    union {
      struct { double num; } Num;
      struct { String str; } String;
      struct { String sym; } Symbol;
    } Atom;
    struct { struct Object *car, *cdr; } Cons;
    struct { struct Object *params, *body, *env; } Fn;
    struct { struct Object *vars, *up; } Env;
  };
} Object;

#endif
