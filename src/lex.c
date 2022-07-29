#include "lex.h"
#include "stream.h"
#include "token.h"
#include <ctype.h>

bool is_whitespace(char c)
{
  return c == ' ' || c == '\t' || c == '\f' || c == '\v';
}

TokenStream *lex(Stream *stream)
{
  TokenStream *tok_stream = new_tok_stream();
  char c;
  while ((c = stream_peek(stream)) != EOF)
  {
    char c = stream_next(stream);
    switch (c)
    {
    case '+':
      tok_stream_push(tok_stream, new_tok(TOK_ADD, "+"));
      break;
    case '-':
      tok_stream_push(tok_stream, new_tok(TOK_SUB, "-"));
      break;
    case '*':
      tok_stream_push(tok_stream, new_tok(TOK_MUL, "*"));
      break;
    case '\\':
      tok_stream_push(tok_stream, new_tok(TOK_QUO, "\\"));
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
        while (stream_next(stream) != '\n')
            continue;
    default:
      if (is_whitespace(c))
      {
        tok_stream_push(tok_stream, new_tok(TOK_WS, "<Whitespace>"));
      }
      else if (isdigit(c))
      {
        int i = 0;
        char *num_lit = calloc(MAX_NUM_CHARS, sizeof(char));
        while (isdigit(c) || c == '.')
        {
          if (i >= MAX_NUM_CHARS)
          {
            tok_stream_push(tok_stream, new_tok(TOK_ERR, "<Error>"));
            break;
          }
          num_lit[i++] = c;
          stream_next(stream);
        }
        if (!isdigit(num_lit[i - 1]))
        {
          tok_stream_push(tok_stream, new_tok(TOK_ERR, "<Error>"));
          break;
        }
      }
      else if (isalpha(c) || c == '_')
      {
        int i = 0;
        char *ident = calloc(MAX_IDENT_CHARS, sizeof(char));
        while (isalnum(c))
        {
          if (i >= MAX_IDENT_CHARS)
          {
            tok_stream_push(tok_stream, new_tok(TOK_ERR, "<Error>"));
            break;
          }
          ident[i++] = c;
          stream_next(stream);
        }
        tok_stream_push(tok_stream, new_tok(TOK_IDENT, ident));
      }
      else
      {
        tok_stream_push(tok_stream, new_tok(TOK_ERR, "<Error>"));
      }
      break;
    }
  }
  tok_stream_push(tok_stream, new_tok(TOK_EOF, "<Eof>"));
  return tok_stream;
}
