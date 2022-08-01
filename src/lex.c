#include "lex.h"

bool is_whitespace(char c)
{
  return c == ' ' || c == '\t' || c == '\f' || c == '\v' || c == '\n';
}

bool is_keyword(String lit)
{
  return strcmp("let", lit) == 0 || strcmp("lambda", lit) == 0;
}

TokenStream *lex(String src)
{
  TokenStream *tok_stream = new_tok_stream();
  for (size_t i = 0; i < strlen(src); i++)
  {
    char c = src[i];
    switch (c)
    {
    case '+':
      tok_stream_push(tok_stream, new_tok(TOK_ADD, "+", i, i + 1));
      break;
    case '-':
      tok_stream_push(tok_stream, new_tok(TOK_SUB, "-", i, i + 1));
      break;
    case '*':
      tok_stream_push(tok_stream, new_tok(TOK_MUL, "*", i, i + 1));
      break;
    case '/':
      tok_stream_push(tok_stream, new_tok(TOK_QUO, "/", i, i + 1));
      break;
    case '%':
      tok_stream_push(tok_stream, new_tok(TOK_MOD, "%", i, i + 1));
      break;
    case '(':
      tok_stream_push(tok_stream, new_tok(TOK_LPAREN, "(", i, i + 1));
      break;
    case ')':
      tok_stream_push(tok_stream, new_tok(TOK_RPAREN, ")", i, i + 1));
      break;
    case ';':
      while (src[i] != '\n')
      {
        if (src[i] == EOF)
          break;
        i++;
        continue;
      }
      break;
    default:
      if (is_whitespace(c))
      {
        continue;
      }
      else if (isdigit(c))
      {
        char *num_lit = calloc(MAX_NUM_CHARS, sizeof(char));
        size_t start = i;
        while (isdigit(c) || c == '.')
        {
          if (i - start >= MAX_NUM_CHARS)
          {
            tok_stream_push(tok_stream,
                            new_tok(TOK_ERR, "<Error>", i - strlen(num_lit), i));
            break;
          }
          num_lit[i++ - start] = c;
          c = src[i];
        }
        if (!isdigit(num_lit[i - start - 1]))
        {
          tok_stream_push(tok_stream,
                          new_tok(TOK_ERR, "<Error>", i - strlen(num_lit), i));
          continue;
        }
        tok_stream_push(tok_stream,
                        new_tok(TOK_NUMBER, num_lit, i - strlen(num_lit), i));
        i--;
      }
      else if (isalpha(c) || c == '_')
      {
        size_t start = i;
        char *ident = calloc(MAX_IDENT_CHARS, sizeof(char));
        while (isalnum(c))
        {
          if (i - start >= MAX_IDENT_CHARS)
          {
            tok_stream_push(tok_stream,
                            new_tok(TOK_ERR, "<Error>", i - strlen(ident), i));
            break;
          }
          ident[i++ - start] = c;
          c = src[i];
        }
        if (is_keyword(ident))
        {
          if (strcmp("let", ident) == 0)
            tok_stream_push(tok_stream,
                            new_tok(TOK_LET, "let", i - strlen(ident), i));
          else if (strcmp("lambda", ident) == 0)
            tok_stream_push(tok_stream,
                            new_tok(TOK_LAMBDA, "lambda", i - strlen(ident), i));
          else
            tok_stream_push(tok_stream,
                            new_tok(TOK_ERR, "<Error>", i - strlen(ident), i));
        }
        else
        {
          tok_stream_push(tok_stream, new_tok(TOK_IDENT, ident, i - strlen(ident), i));
        }
        i--;
      }
      else
      {
        tok_stream_push(tok_stream, new_tok(TOK_ERR, "<Error>", i, i));
        continue;
      }
      break;
    }
  }
  tok_stream_push(tok_stream, new_tok(TOK_EOF, "<Eof>", 0, 0));
  return tok_stream;
}
