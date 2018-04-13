#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 8192*1024

int main(int argc, char *argv[]){
	char *a, *b;
	int i;
	unsigned long dscr;
        unsigned long foo;

	if (argc < 2)
		dscr = 0;
	else
		dscr = atol(argv[1]);

	 __asm __volatile ("mtspr 0x11, %0" : "=r"(dscr));


        asm ("mfdscr %0  \n\t" :  "=r" (foo) ::);
        printf("BEGIN: dscr = %lx\n", foo);
	foo = 0;

	a = malloc(MAX);
	b = malloc(MAX);

	for (i=0; i < 1024; i++) {
		memset(a, i, MAX);
		memcpy(b, a, MAX);
	}

        asm ("mfdscr %0  \n\t" :  "=r" (foo) ::);
        printf("END: dscr = %lx\n", foo);
}
