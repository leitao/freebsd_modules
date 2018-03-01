#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>

void dump(void);

void dump(){
	register_t msr;
	msr = mfmsr();
	printf("MSR: %lx\n", msr);
}


static int handler(struct module *module, int e, void *arg) {
        switch (e) {

        case MOD_LOAD:
		dump();
                break;

        case MOD_UNLOAD:
                return 0;
        default:
                e = EOPNOTSUPP;
                break;
        }

        return(e);

}


static moduledata_t msr_data = {

    "msr",  

     handler, 

     NULL

};

DECLARE_MODULE(htm, msr_data, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
