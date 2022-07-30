#include "lex.h"
#include "stream.h"
#include "token.h"
#include <ctype.h>

bool is_whitespace(char c) {
  return c == ' ' || c == '\t' || c == '\f' || c == '\v';
}

TokenStream *lex(Stream *stream) {
  TokenStream *tok_stream = new_tok_stream();
  char c;
  while ((c = stream_peek(stream)) != EOF) {
    switch (c) {
    case '+':
      tok_stream_push(tok_stream, new_tok(TOK_ADD, "+"));
      stream_next(stream);
      break;
    case '-':
      tok_stream_push(tok_stream, new_tok(TOK_SUB, "-"));
      stream_next(stream);
      break;
    case '*':
      tok_stream_push(tok_stream, new_tok(TOK_MUL, "*"));
      stream_next(stream);
      break;
    case '\\':
      tok_stream_push(tok_stream, new_tok(TOK_QUO, "\\"));
      stream_next(stream);
      break;
    case '%':
      tok_stream_push(tok_stream, new_tok(TOK_MOD, "%"));
      stream_next(stream);
      break;
    case '(':
      tok_stream_push(tok_stream, new_tok(TOK_LPAREN, "("));
      stream_next(stream);
      break;
    case ')':
      tok_stream_push(tok_stream, new_tok(TOK_RPAREN, ")"));
      stream_next(stream);
      break;
    case ';':
      while (stream_next(stream) != '\n')
        continue;
    default:
      if (is_whitespace(c)) {
        stream_next(stream);
      } else if (isdigit(c)) {
        int i = 0;
        char *num_lit = calloc(MAX_NUM_CHARS, sizeof(char));
        stream_next(stream);
        while (isdigit(c) || c == '.') {
          if (i >= MAX_NUM_CHARS) {
            tok_stream_push(tok_stream, new_tok(TOK_ERR, "<Error>"));
            break;
          }
          num_lit[i++] = c;
          c = stream_next(stream);
        }
        if (!isdigit(num_lit[i - 1])) {
          tok_stream_push(tok_stream, new_tok(TOK_ERR, "<Error>"));
          stream_next(stream);
          break;
        }
        tok_stream_push(tok_stream, new_tok(TOK_NUMBER, num_lit));
      } else if (isalpha(c) || c == '_') {
        int i = 0;
        char *ident = calloc(MAX_IDENT_CHARS, sizeof(char));
        while (isalnum(c)) {
          if (i >= MAX_IDENT_CHARS) {
            tok_stream_push(tok_stream, new_tok(TOK_ERR, "<Error>"));
            stream_next(stream);
            break;
          }
          ident[i++] = c;
          c = stream_next(stream);
        }
        tok_stream_push(tok_stream, new_tok(TOK_IDENT, ident));
      } else {
        tok_stream_push(tok_stream, new_tok(TOK_ERR, "<Error>"));
        stream_next(stream);
      }
      break;
    }
  }
  tok_stream_push(tok_stream, new_tok(TOK_EOF, "<Eof>"));
  return tok_stream;
}
