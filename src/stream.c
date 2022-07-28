#include "stream.h"

Stream *new_stream_from_path(char *path)
{
	Stream *stream = calloc(1, sizeof(Stream));
	stream->path = path;
	stream->pos = 0;
	FILE *file = fopen(path, "r");
	if (!file)
	{
		printf("Error: file \"%s\" does not exist\n", path);
	}
	char *buf = calloc(1024, sizeof(char));
	size_t read;
	size_t size = 1024;
	while ((read = fread(buf, 1, 1024, file)) > 0)
	{
		size += 1024;
		buf = realloc(buf, size);
	}
	buf[size] = '\0';
	stream->src = buf;
	return stream;
}

Stream *new_stream_from_string(String src)
{
	Stream *stream = calloc(1, sizeof(Stream));
	stream->src = src;
	stream->pos = 0;
	return stream;
}

int stream_next(Stream *stream)
{
	if (strlen(stream->src) > stream->pos)
		return stream->src[stream->pos++];
	return EOF;
}

int stream_peek(Stream *stream)
{
	if (strlen(stream->src) > stream->pos)
		return stream->src[stream->pos];
	return EOF;
}
