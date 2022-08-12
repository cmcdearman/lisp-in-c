#include "lex.h"
#include "parse.h"

int main()
{
  char *src = "(+ (/ 6 (* 1.5 2)) (- 1 (mod 5 2))) ; 2.0";
  //char *src = "(1 2)";
  print_tok_stream(lex(src));
  print_object(parse(lex(src)));
  printf("\n");
  return 0;
}
