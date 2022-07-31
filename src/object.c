#include "object.h"

void print_object(Object *obj) {
  while (obj != NULL) {
    switch (obj->type) {
    case OBJ_NUMBER:
      printf("%.1f", obj->Atom.Num.num);
      obj = obj->Cons.cdr;
      break;
    case OBJ_STRING:
      printf("%s", obj->Atom.String.str);
      obj = obj->Cons.cdr;
      break;
    case OBJ_SYMBOL:
      printf("%s", obj->Atom.Symbol.sym);
      obj = obj->Cons.cdr;
      break;
    case OBJ_CONS:
      printf("(");
      print_object(obj->Cons.car);
      printf(",");
      print_object(obj->Cons.cdr);
      printf(")");
      obj = obj->Cons.cdr;
      break;
    default:
      fprintf(stderr, "unknown object");
      exit(1);
    }
  }
}

void debug_print_object(Object *obj) {
  while (obj != NULL) {
    switch (obj->type) {
    case OBJ_NUMBER:
      printf("Atom(Number(%f))", obj->Atom.Num.num);
      obj = obj->Cons.cdr;
      break;
    case OBJ_STRING:
      printf("Atom(String(%s))", obj->Atom.String.str);
      obj = obj->Cons.cdr;
      break;
    case OBJ_SYMBOL:
      printf("Atom(Symbol(%s))", obj->Atom.Symbol.sym);
      obj = obj->Cons.cdr;
      break;
    case OBJ_CONS:
      printf("Cons { car: ");
      debug_print_object(obj->Cons.car);
      printf(", cdr: ");
      debug_print_object(obj->Cons.cdr);
      printf(" }");
      obj = obj->Cons.cdr;
      break;
    default:
      fprintf(stderr, "unknown object");
      exit(1);
    }
  }
}

void json_print_object(Object *obj) {
  while (obj != NULL) {
    switch (obj->type) {
    case OBJ_NUMBER:
      printf("%f", obj->Atom.Num.num);
      obj = obj->Cons.cdr;
      break;
    case OBJ_STRING:
      printf("%s", obj->Atom.String.str);
      obj = obj->Cons.cdr;
      break;
    case OBJ_SYMBOL:
      printf("%s", obj->Atom.Symbol.sym);
      obj = obj->Cons.cdr;
      break;
    case OBJ_CONS:
      printf("{\n\t\"car\": ");
      json_print_object(obj->Cons.car);
      printf(",\n\"cdr\": ");
      json_print_object(obj->Cons.cdr);
      printf("\n}");
      obj = obj->Cons.cdr;
      break;
    default:
      fprintf(stderr, "unknown object");
      exit(1);
    }
  }
}
