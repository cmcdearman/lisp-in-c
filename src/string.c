#include "string.h"

String string_from_file(String path)
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
  if (!(buf = (char *)malloc(len + 1)))
    fprintf(stderr, "Error: could not allocate string memory\n"), exit(1);
  if (!fread(buf, 1, len, file))
    fprintf(stderr, "Error: could not read from file\n"), exit(1);
  buf[len] = '\0';
  fclose(file);

  return buf;
}

String string_cat(String str1, String str2) {
  char *str = malloc((strlen(str1) + strlen(str2)) * sizeof(char));
  strcpy(str, str1);
  strcat(str, str2);
  return str;
}