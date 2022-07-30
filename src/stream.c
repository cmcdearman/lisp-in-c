#include "stream.h"

Stream *new_stream_from_path(char *path)
{
  long len;
  char *buf;
  FILE *file;

  if (!(file = fopen(path, "r")))
    fprintf(stderr, "Error: file \"%s\" does not exist\n", path), exit(1);
  if (fseek(file, 0, SEEK_END) == -1)
    fprintf(stderr, "Error: could not seek to end of file\n"), exit(1);
  if ((len = ftell(file)) == -1)
    fprintf(stderr, "Error: could not seek to end of file\n"), exit(1);
  if (fseek(file, 0, SEEK_SET) == -1)
    fprintf(stderr, "Error: could not check file length\n"), exit(1);
  if (!(buf = (char *) malloc(len+1)))
    fprintf(stderr, "Error: could not allocate string memory\n"), exit(1);
  if (!fread(buf, 1, len, file))
    fprintf(stderr, "Error: could not read from file\n"), exit(1);
  buf[len] = '\0';
  fclose(file);

  Stream *stream = calloc(1, sizeof(Stream));
  stream->path = path;
  stream->cur = 0;
  stream->peek = 0;
  stream->src = buf;
  return stream;
}

Stream *new_stream_from_string(String src)
{
  Stream *stream = calloc(1, sizeof(Stream));
  stream->src = src;
  stream->cur = 0;
  stream->peek = 0;
  return stream;
}

int stream_next(Stream *stream)
{
  if (strlen(stream->src) >= stream->peek)
  {
    stream->peek++;
    return stream->src[++stream->cur];
  }
  return EOF;
}

int stream_peek(Stream *stream)
{
  if (strlen(stream->src) >= stream->peek)
    return stream->src[stream->peek];
  return EOF;
}
