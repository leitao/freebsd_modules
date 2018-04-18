#include <stdio.h>
#include <machine/cpufunc.h>

int main(){
	long pvr;

        __asm __volatile ("mfpvr %0" : "=r"(pvr));	

	printf("PVR = %lx\n", pvr);

	return 0;
}
