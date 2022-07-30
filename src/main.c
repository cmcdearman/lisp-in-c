#include <stdio.h>
#include "stream.h"
#include "token.h"
#include "lex.h"

int main()
{
  Stream *stream = new_stream_from_path("examples/simple.egl");
  TokenStream *tokens = lex(stream);
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
