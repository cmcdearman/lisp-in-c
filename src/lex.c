#include "lex.h"

bool is_whitespace(char c) {
  return c == ' ' || c == '\t' || c == '\f' || c == '\v';
}

TokenStream *lex(char *src) {
  TokenStream *stream = new_tok_stream();
  for (int i = 0; i < strlen(src); i++) {
    char c = src[i];
    switch (c) {
    case '+':
      tok_stream_push(stream, new_tok(TOK_ADD, "+"));
      break;
    case '-':
      tok_stream_push(stream, new_tok(TOK_SUB, "-"));
      break;
    case '*':
      tok_stream_push(stream, new_tok(TOK_MUL, "*"));
      break;
    case '\\':
      tok_stream_push(stream, new_tok(TOK_QUO, "\\"));
      break;
    case '%':
      tok_stream_push(stream, new_tok(TOK_MOD, "%"));
      break;
    case '(':
      tok_stream_push(stream, new_tok(TOK_LPAREN, "("));
      break;
    case ')':
      tok_stream_push(stream, new_tok(TOK_RPAREN, ")"));
      break;
    default:
      if (is_whitespace(c)) {
        tok_stream_push(stream, new_tok(TOK_WS, "<Whitespace>"));
      } else if (isdigit(c)) {
        char *num_lit = calloc(MAX_NUM_CHARS, sizeof(char));
        int start = i;
        while (isdigit(c) || c == '.') {
          if (i - start == MAX_NUM_CHARS) {
            tok_stream_push(stream, new_tok(TOK_ERR, "<Error>"));
            break;
          }
          num_lit[i - start] = c;
          i++;
        }
        if (!isdigit(num_lit[i - start])) {
					tok_stream_push(stream, new_tok(TOK_ERR, "<Error>"));
					break;
        }
      } else {
        tok_stream_push(stream, new_tok(TOK_ERR, "<Error>"));
      }
      break;
    }
  }
  return stream;
}
