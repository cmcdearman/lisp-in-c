#include "lex.h"
#include "parse.h"

int main()
{
  print_object(parse(lex("(+ (/ 6 (* 1.5 2)) (- 1 (% 5 2))) ; 2.0")));
  return 0;
}
