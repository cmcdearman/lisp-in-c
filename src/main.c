#include <stdio.h>

int main() {
	FILE* file = fopen("examples/simple.egl", "r");
	if (!file) {
		printf("Error: file does not exist\n");
		return -1;
	}
	int c;
	while ((c = getc(file)) != EOF)
		putchar(c);
	fclose(file);
	return 0;
}
