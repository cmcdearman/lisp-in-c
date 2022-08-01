#include <stdio.h>
#include "token.h"
#include "lex.h"
#include "string.h"
#include "parse.h"

int main()
{
  TokenStream *tokens = lex(string_from_file("examples/deadSimple.egl"));
//  while (true)
//  {
//    Token *tok = tok_stream_next(tokens);
//    if (tok->type != TOK_EOF)
//    {
//      printf(
//          "Token { Type: %s, Lit: %s } - <%zu, %zu>\n",
//          tok_type_to_str(tok->type),
//          tok->lit,
//          tok->span->start,
//          tok->span->end);
//      tok = NULL;
//    }
//    else
//      break;
//  }
  while (tok_stream_peek(tokens)->type != TOK_EOF) {
    Object *ast = parse(tokens);
    print_object(ast);
    printf("\n");
    tok_stream_next(tokens);
  }
  return 0;
}
