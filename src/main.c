#include <stdio.h>
#include "token.h"
#include "lex.h"
#include "string.h"
#include "parse.h"

int main()
{
  print_object(parse(lex(string_from_file("examples/deadSimple.egl"))));
  return 0;
}
