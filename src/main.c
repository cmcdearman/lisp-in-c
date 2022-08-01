#include "lex.h"
#include "parse.h"

int main()
{
  char *src = "(+ (/ 6 (* 1.5 2)) (- 1 (% 5 2))) ; 2.0";
  print_tok_stream(lex(src));
  print_object(parse(lex(src)));
  return 0;
}
