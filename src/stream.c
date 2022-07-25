#include "stream.h"

Stream* new_stream_from_path(char* path) {
	Stream* stream;
	stream->path = path;
	stream->pos = 0;
	FILE* file = fopen(path, "r");
	if (!file) {
		printf("Error: file \"%s\" does not exist\n", path);
	}	
	return stream;
}

Stream* new_stream_from_string(String* src) {
	Stream* stream;	
	stream->src = src;
	stream->pos = 0;
	return stream;
}

char stream_next(Stream *stream) {
	return 0;
}
