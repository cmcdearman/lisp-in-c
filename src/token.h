#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum {
  TOK_EOF,
  TOK_WS,
  TOK_ERR,
  TOK_COMMENT,

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

//static const char *TOKEN_TYPE_STR[] = {
//    [TOK_EOF] = "<EOF>", [TOK_WS] = "<Whitespace>", [TOK_ERR] = "<Error>",
//    [TOK_ADD] = "+",     [TOK_SUB] = "-",           [TOK_MUL] = "*",
//    [TOK_QUO] = "/",     [TOK_MOD] = "%",           [TOK_LPAREN] = "(",
//    [TOK_RPAREN] = ")",  [TOK_LET] = "let",         [TOK_LAMBDA] = "lambda"};

typedef struct {
  size_t start;
  size_t end;
} Span;

typedef struct {
  TokenType type;
  char *lit;
} Token;

Token *new_tok(TokenType, char*);

#define START_TOK_SIZE 10000UL

typedef struct {
  Token *tokens;
  size_t count;
  size_t size;
	size_t pos;
} TokenStream;

TokenStream *new_tok_stream();
void tok_stream_push(TokenStream*, Token*);
Token* tok_stream_next(TokenStream*);
Token* tok_stream_peek(TokenStream*);

#endif
