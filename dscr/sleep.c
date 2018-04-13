#include <stdio.h>
#include <unistd.h>
  
int main(){
        unsigned long foo;

        printf("Hello\n");
        asm ("mfdscr %0  \n\t" :  "=r" (foo) ::);

        printf("dscr is %lx\n", foo);

        asm ("li  9, 5  \n\t");
        asm ("mtdscr 9  \n\t");

	sleep(3);
	foo = 0;
        asm ("mfdscr %0  \n\t" :  "=r" (foo) ::);
        printf("now dscr is %lx\n", foo);
        printf("End\n");
        return 0;
}

