#include "lex.h"
#include "parse.h"

int main()
{
  char *src = "(+ (/ 6 (* 1.5 2)) (- 1 (mod 5 2))) ; 2.0";
  TokenStream *stream = lex(src);
  // print_tok_stream(stream);
  Object *ast = parse(stream);
  print_object(ast);
  printf("\n");
  return 0;
}
