#include <stdio.h>
#include "stream.h"
#include "token.h"
#include "lex.h"

int main() {
	Stream* stream = new_stream_from_path("examples/simple.egl");
	//int c;
	//while ((c = stream_next(stream)) != EOF) {
	//	putchar(c);
	//}
	TokenStream *tokens = lex(stream);
	while (true) {
		Token *tok = malloc(sizeof(Token));
		if ((tok = tok_stream_next(tokens))->type != TOK_EOF) {
			printf("Token { Type: Type, Lit: %s}", tok->lit);	
			free(tok);
		} else {
			return 0;
		}
	}
	return 0;
}
