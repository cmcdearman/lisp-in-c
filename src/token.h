#ifndef TOKEN_H
#define TOKEN_H

#include "string.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
  TOK_EOF,
  TOK_ERR,

  TOK_IDENT,
  TOK_NUMBER,
  TOK_STRING,

  TOK_ADD,
  TOK_SUB,
  TOK_MUL,
  TOK_QUO,
  TOK_MOD,

  TOK_LPAREN,
  TOK_RPAREN,

  TOK_LET,
  TOK_LAMBDA
} TokenType;

typedef struct {
  size_t start;
  size_t end;
} Span;

Span *new_span(size_t start, size_t end);
void span_free(Span *);

typedef struct {
  TokenType type;
  char *lit;
  Span *span;
} Token;

Token *new_tok(TokenType, char *, size_t, size_t);
void tok_free(Token *);
String tok_type_to_str(TokenType type);
void print_token(Token *);

#define START_TOK_SIZE 10000UL

typedef struct {
  Token *tokens;
  size_t count;
  size_t size;
  size_t pos;
} TokenStream;

TokenStream *new_tok_stream();
void tok_stream_free(TokenStream *);
void tok_stream_push(TokenStream *, Token *);
Token *tok_stream_next(TokenStream *);
Token *tok_stream_peek(TokenStream *);
void print_tok_stream(TokenStream *);

#endif
