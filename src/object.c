#include "object.h"

void print_object(Object *obj) {
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
      printf("Sexpr::Atom::Literal::Number(%ld)", obj->Atom.Num.num);
      obj = obj->Cons.cdr;
      break;
    case OBJ_STRING:
      printf("Sexpr::Atom::Literal::String(%s)", obj->Atom.String.str);
      obj = obj->Cons.cdr;
      break;
    case OBJ_SYMBOL:
      printf("Sexpr::Atom::Literal::Symbol(%s)", obj->Atom.Symbol.sym);
      obj = obj->Cons.cdr;
      break;
    case OBJ_CONS:
      printf("Sexpr::Cons { car: ");
      print_object(obj->Cons.car);
      printf(", cdr: ");
      print_object(obj->Cons.cdr);
      printf(" }");
      obj = obj->Cons.cdr;
      break;
    default:
      fprintf(stderr, "unknown object");
      exit(1);
    }
  }
}
