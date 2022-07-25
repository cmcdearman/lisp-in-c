#include "token.h"

Token new_tok(TokenType type, char *lit) {
  Token tok;
  tok.type = type;
  tok.lit = lit;
  // tok->filepath = filepath;
  // tok->span = span;
  return tok;
}
TokenStream *new_tok_stream() {
  TokenStream *stream = calloc(1, sizeof(TokenStream));
  stream->tokens = calloc(START_TOK_SIZE, sizeof(Token));
  stream->count = 0;
	stream->pos = 0;
  return stream;
}

void tok_stream_push(TokenStream *stream, Token tok) {
  if (stream->count >= stream->size) {
    Token *tmp = stream->tokens;
    stream->tokens = calloc(stream->size *= 2, sizeof(Token));
    for (int i = 0; i < stream->count; i++) {
      stream->tokens[i] = tmp[i];
    }
  }
  stream->tokens[stream->count++] = tok;
}

Token* tok_stream_next(TokenStream* stream) {
	return &stream->tokens[stream->pos++];
}

Token* tok_stream_peek(TokenStream* stream) {
	return &stream->tokens[stream->pos];
}
