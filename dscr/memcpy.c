#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 8192*1024

int main(int argc, char *argv[]){
	char *a, *b;
	int i;
	unsigned long dscr;

	if (argc < 2)
		dscr = 0;
	else
		dscr = atol(argv[1]);

	printf("dscr = %lx\n", dscr);

	a = malloc(MAX);
	b = malloc(MAX);

	for (i=0; i < 1024; i++) {
		memset(a, i, MAX);
		memcpy(b, a, MAX);
	}
	printf("b now has %x\n", b[1]);
}
