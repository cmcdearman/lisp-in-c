#ifndef OBJECT_H
#define OBJECT_H

#include "string.h"
#include "util.h"

typedef enum {
  OBJ_NUMBER,
  OBJ_STRING,
  OBJ_SYMBOL,
  OBJ_CONS,
  OBJ_FN,
  OBJ_ENV
} ObjectType;

struct Object;

typedef struct Object {
  ObjectType type;
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

void print_object(Object *);
void debug_print_object(Object *);
void json_print_object(Object *);

#endif
