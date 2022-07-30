#include <stdio.h>
#include "token.h"
#include "lex.h"
#include "string.h"

int main()
{
  String src = string_from_file("examples/simple.egl");
  TokenStream *tokens = lex(src);
  while (true)
  {
    Token *tok = tok_stream_next(tokens);
    if (tok->type != TOK_EOF)
    {
      printf("Token { Type: Type, Lit: %s}\n", tok->lit);
      tok = NULL;
    }
    else
      break;
  }
  return 0;
}
