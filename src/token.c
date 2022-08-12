#include "token.h"

Span *new_span(size_t start, size_t end)
{
  Span *span = malloc(sizeof(Span));
  span->start = start;
  span->end = end;
  return span;
}

void span_free(Span *span) {
  free(span);
  span = NULL;
}

Token *new_tok(TokenType type, char *lit, size_t start, size_t end)
{
  Token *tok = malloc(sizeof(Token));
  tok->type = type;
  tok->lit = lit;
  tok->span = new_span(start, end);
  return tok;
}

void tok_free(Token *tok) {
  span_free(tok->span);
  free(tok);
  tok = NULL;
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

void print_token(Token *tok)
{
  printf(
      "Token { Type: %s, Lit: %s } - <%zu, %zu>\n",
      tok_type_to_str(tok->type),
      tok->lit,
      tok->span->start,
      tok->span->end);
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

void tok_stream_free(TokenStream *stream) {
  for (size_t i = 0; i < stream->count; i++) {
    tok_free(&stream->tokens[i]);
  }
  free(stream);
  stream = NULL;
}

void tok_stream_push(TokenStream *stream, Token *tok)
{
  if (stream->count == stream->size)
  {
    Token *tmp;
    stream->size *= 2;
    tmp = realloc(stream->tokens, stream->size * sizeof(Token));
    if (!tmp) {
      fprintf(stderr, "error: out of usable virtual memory");
      exit(1);
    }
    stream->tokens = tmp;
  }
  stream->tokens[stream->count++] = *tok;
}

Token *tok_stream_next(TokenStream *stream)
{
  if (stream->size > stream->pos)
    return &stream->tokens[stream->pos++];
  return new_tok(TOK_EOF, "<Eof>", 0, 0);
}

Token *tok_stream_peek(TokenStream *stream)
{
  if (stream->size > stream->pos)
    return &stream->tokens[stream->pos];
  return new_tok(TOK_EOF, "<Eof>", 0, 0);
}

void print_tok_stream(TokenStream *stream)
{
  while (true)
  {
    Token *tok = tok_stream_next(stream);
    if (tok->type != TOK_EOF)
    {
      print_token(tok);
    }
    else
      break;
  }
}
