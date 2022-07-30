#include "token.h"

Span *new_span(size_t start, size_t end)
{
  Span *span = malloc(sizeof(Span *));
  span->start = start;
  span->end = end;
  return span;
}

Token *new_tok(TokenType type, char *lit, size_t start, size_t end)
{
  Token *tok = malloc(sizeof(Token));
  tok->type = type;
  tok->lit = lit;
  tok->span = new_span(start, end);
  return tok;
}

String tok_type_to_str(TokenType type)
{
  switch (type)
  {
  case TOK_EOF:
    return "EOF";
  case TOK_ERR:
    return "Error";
  case TOK_IDENT:
    return "Ident";
  case TOK_NUMBER:
    return "Number";
  case TOK_STRING:
    return "String";
  case TOK_ADD:
    return "+";
  case TOK_SUB:
    return "-";
  case TOK_MUL:
    return "*";
  case TOK_QUO:
    return "/";
  case TOK_MOD:
    return "%";
  case TOK_LPAREN:
    return "(";
  case TOK_RPAREN:
    return ")";
  case TOK_LET:
    return "let";
  case TOK_LAMBDA:
    return "lambda";
  }
  return "";
}

TokenStream *new_tok_stream()
{
  TokenStream *stream = calloc(1, sizeof(TokenStream));
  stream->tokens = calloc(START_TOK_SIZE, sizeof(Token));
  stream->count = 0;
  stream->pos = 0;
  stream->size = START_TOK_SIZE;
  return stream;
}

void tok_stream_push(TokenStream *stream, Token *tok)
{
  if (stream->count == stream->size)
  {
    stream->size *= 2;
    stream->tokens = realloc(stream->tokens, stream->size * sizeof(Token));
  }
  stream->tokens[stream->count++] = *tok;
}

Token *tok_stream_next(TokenStream *stream)
{
  if (stream->size >= stream->pos)
    return &stream->tokens[stream->pos++];
  return new_tok(TOK_EOF, "<Eof>", 0, 0);
}

Token *tok_stream_peek(TokenStream *stream)
{
  if (stream->size >= stream->pos)
    return &stream->tokens[stream->pos];
  return new_tok(TOK_EOF, "<Eof>", 0, 0);
}
