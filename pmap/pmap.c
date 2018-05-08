#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/sbuf.h>
#include <sys/kdb.h>
#include <sys/queue.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/tree.h>
#define AIM 1
#include <vm/vm.h>
#include <vm/pmap.h>
#include <machine/pmap.h>


void dump(void);
void dump2(void);



void dump(){
	struct slbtnode *slb;
	struct pmap *p;

	p = kernel_pmap;


	slb = p->pm_slb_tree_root;

	printf("Kernel_pmap is at %p\n", slb);
}


void dump2(){
	printf("By\n");
}

static int handler(struct module *module, int e, void *arg) {
        switch (e) {

        case MOD_LOAD:
		dump();
                break;

        case MOD_UNLOAD:
		dump2();
                return 0;
        default:
                e = EOPNOTSUPP;
                break;
        }

        return(e);

}


static moduledata_t pmap_data = {

    "pmap",  

     handler, 

     NULL

};

DECLARE_MODULE(pmap, pmap_data, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
