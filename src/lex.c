#include "lex.h"

bool is_whitespace(char c) {
  return c == ' ' || c == '\t' || c == '\f' || c == '\v' || c == '\n';
}

TokenStream *lex(String src) {
  TokenStream *tok_stream = new_tok_stream();
  for (int i = 0; i < strlen(src); i++) {
    char c = src[i];
    switch (c) {
    case '+':
      tok_stream_push(tok_stream, new_tok(TOK_ADD, "+"));
      break;
    case '-':
      tok_stream_push(tok_stream, new_tok(TOK_SUB, "-"));
      break;
    case '*':
      tok_stream_push(tok_stream, new_tok(TOK_MUL, "*"));
      break;
    case '/':
      tok_stream_push(tok_stream, new_tok(TOK_QUO, "/"));
      break;
    case '%':
      tok_stream_push(tok_stream, new_tok(TOK_MOD, "%"));
      break;
    case '(':
      tok_stream_push(tok_stream, new_tok(TOK_LPAREN, "("));
      break;
    case ')':
      tok_stream_push(tok_stream, new_tok(TOK_RPAREN, ")"));
      break;
    case ';':
      while (src[i] != '\n')
      {
        i++;
        continue;
      }
      break;
    default:
      if (is_whitespace(c)) {
        continue;
      } else if (isdigit(c)) {
        char *num_lit = calloc(MAX_NUM_CHARS, sizeof(char));
        int start = i;
        while (isdigit(c) || c == '.') {
          if (i-start >= MAX_NUM_CHARS) {
            tok_stream_push(tok_stream, new_tok(TOK_ERR, "<Error>"));
            break;
          }
          num_lit[i++ - start] = c;
          c = src[i];
        }
        if (!isdigit(num_lit[i - start - 1])) {
          tok_stream_push(tok_stream, new_tok(TOK_ERR, "<Error>"));
          continue;
        }
        tok_stream_push(tok_stream, new_tok(TOK_NUMBER, num_lit));
        i--;
      } else if (isalpha(c) || c == '_') {
        int start = i;
        char *ident = calloc(MAX_IDENT_CHARS, sizeof(char));
        while (isalnum(c)) {
          if (i-start >= MAX_IDENT_CHARS) {
            tok_stream_push(tok_stream, new_tok(TOK_ERR, "<Error>"));
            break;
          }
          ident[i++ - start] = c;
          c = src[i];
        }
        tok_stream_push(tok_stream, new_tok(TOK_IDENT, ident));
      } else {
        tok_stream_push(tok_stream, new_tok(TOK_ERR, "<Error>"));
        continue;
      }
      break;
    }
  }
  tok_stream_push(tok_stream, new_tok(TOK_EOF, "<Eof>"));
  return tok_stream;
}
