#include "parse.h"

Object *parse_atom(TokenStream *stream) {
  Object *atom = calloc(1, sizeof(Object));
  switch (tok_stream_peek(stream)->type) {
  case TOK_NUMBER:
    atom->Atom.Num.num = strtod(tok_stream_next(stream)->lit, NULL);
    atom->type = OBJ_NUMBER;
    return atom;
  case TOK_STRING:
    atom->Atom.String.str = tok_stream_next(stream)->lit;
    atom->type = OBJ_STRING;
    return atom;
  case TOK_IDENT:
    atom->Atom.Symbol.sym = tok_stream_next(stream)->lit;
    atom->type = OBJ_SYMBOL;
    return atom;
  case TOK_LET:
    atom->Atom.Symbol.sym = tok_stream_next(stream)->lit;
    atom->type = OBJ_SYMBOL;
    return atom;
  case TOK_LAMBDA:
    atom->Atom.Symbol.sym = tok_stream_next(stream)->lit;
    atom->type = OBJ_SYMBOL;
    return atom;
  case TOK_ADD:
  case TOK_SUB:
  case TOK_MUL:
  case TOK_QUO:
  case TOK_MOD:
    atom->Atom.Symbol.sym = tok_stream_next(stream)->lit;
    atom->type = OBJ_SYMBOL;
    return atom;
  default:
    fprintf(stderr, "Unknown token");
    exit(1);
  }
}

Object *parse_list(TokenStream *stream) {
  Object *cons = malloc(sizeof(Object*));
  Object *car = parse(stream);
  Object *cdr;
  cons->type = OBJ_CONS;

  if (tok_stream_peek(stream)->type == TOK_RPAREN) {
    tok_stream_next(stream);
    cdr = NULL;
  } else {
    cdr = parse_list(stream);
  }
  cons->Cons.car = car;
  cons->Cons.cdr = cdr;
  return cons;
}

Object *parse(TokenStream *stream) {
  switch (tok_stream_peek(stream)->type) {
  case TOK_LPAREN:
    tok_stream_next(stream);
    return parse_list(stream);
  default:
    return parse_atom(stream);
  }
}
