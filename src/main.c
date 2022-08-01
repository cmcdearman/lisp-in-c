#include "lex.h"
#include "parse.h"

int main()
{
  print_object(parse(lex("(- 1 (% 5 2)) ; 0")));
  return 0;
}
