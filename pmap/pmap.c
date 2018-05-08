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
	struct slbtnode *slbtn;
	struct pmap *p;
	struct pvo_tree *pvo;
	//struct pvo_entry *pve;
	int indx;

	p = kernel_pmap;

	slbtn = p->pm_slb_tree_root;
	pvo = &p->pmap_pvo;

	printf("Kernel_pmap: %p\n", p);
	printf("Kernel_pmap->pm_slb_tree_root:  %p\n", slbtn);
	printf("Kernel_pmap->pm_slb_len:  %d\n", p->pm_slb_len);
	printf("Kernel_pmap->pmap_pvo:  %p\n", pvo);

	printf("virtual_avail: %lx \n", (long) virtual_avail);
	printf("virtual_end:  %lx \n", (long) virtual_end);

	for (indx = 0; phys_avail[indx + 1] != 0; indx += 2) {                                             
                vm_paddr_t size1 = phys_avail[indx + 1] - phys_avail[indx];

		printf("0x%016jx - 0x%016jx, %ju bytes (%ju pages)\n",
                            (uintmax_t)phys_avail[indx],
                            (uintmax_t)phys_avail[indx + 1] - 1,
                            (uintmax_t)size1, (uintmax_t)size1 / PAGE_SIZE);
	}


/*
	do {
		pve = RB_NEXT(pvo, &kernel_pmap->pmap_pvo, pvo)
	} while (pve != NULL);
*/

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
