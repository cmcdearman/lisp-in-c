#include <stdio.h>
#include "token.h"
#include "lex.h"
#include "string.h"
#include "parse.h"

int main()
{
  String src = string_from_file("examples/simple.egl");
  TokenStream *tokens = lex(src);
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
  Object *ast = parse(tokens);
  json_print_object(ast);
  return 0;
}
