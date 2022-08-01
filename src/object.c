#include "object.h"

Object *cons(Object *car, Object *cdr) {
  Object *cons = malloc(sizeof(Object));
  cons->type = OBJ_CONS;
  cons->Cons.car = car;
  cons->Cons.cdr = cdr;
  return cons;
}

void print_object(Object *obj) {
  switch (obj->type) {
  case OBJ_NUMBER:
    printf("%.1f", obj->Atom.Num.num);
    return;
  case OBJ_STRING:
    printf("%s", obj->Atom.String.str);
    return;
  case OBJ_SYMBOL:
    printf("%s", obj->Atom.Symbol.sym);
    return;
  case OBJ_CONS:
    printf("(");
    print_object(obj->Cons.car);
    printf(",");
    if (!obj->Cons.cdr) {
      printf("null");
      printf(")");
      return;
    }
    print_object(obj->Cons.cdr);
    printf(")");
    return;
  default:
    fprintf(stderr, "unknown object");
    exit(1);
  }
}

void debug_print_object(Object *obj) {
  switch (obj->type) {
  case OBJ_NUMBER:
    printf("Atom(Number(%.1f))", obj->Atom.Num.num);
    return;
  case OBJ_STRING:
    printf("Atom(String(%s))", obj->Atom.String.str);
    return;
  case OBJ_SYMBOL:
    printf("Atom(Symbol(%s))", obj->Atom.Symbol.sym);
    return;
  case OBJ_CONS:
    printf("Cons { car: ");
    debug_print_object(obj->Cons.car);
    printf(", cdr: ");
    if (!obj->Cons.cdr) {
      printf("null");
      printf(" }");
      return;
    }
    debug_print_object(obj->Cons.cdr);
    printf(" }");
    break;
  default:
    fprintf(stderr, "unknown object");
    exit(1);
  }
}

void json_print_object(Object *obj) {
  switch (obj->type) {
  case OBJ_NUMBER:
    printf("%.1f", obj->Atom.Num.num);
    return;
  case OBJ_STRING:
    printf("\"%s\"", obj->Atom.String.str);
    return;
  case OBJ_SYMBOL:
    printf("\"%s\"", obj->Atom.Symbol.sym);
    return;
  case OBJ_CONS:
    printf("{\"car\": ");
    json_print_object(obj->Cons.car);
    printf(",\"cdr\": ");
    if (!obj->Cons.cdr) {
      printf("null");
      printf("}");
      return;
    }
    json_print_object(obj->Cons.cdr);
    printf("}");
    return;
  default:
    fprintf(stderr, "unknown object");
    exit(1);
  }
}
