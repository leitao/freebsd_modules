#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>

#define PSL_HTM                0x0000000100000000UL    /* Hardware Transactional Memory available */

void htm_enable(void);
void htm_disable(void);

void htm_enable(){
       printf("Enabled HTM\n %lx\n", mfmsr());
        mtmsr(mfmsr() | PSL_HTM);
       printf("Enabled HTM\n %lx\n", mfmsr());
}

void htm_disable(){
       printf("Disabling HTM\n %lx\n", mfmsr());
        mtmsr(mfmsr() & ~(PSL_HTM));
       printf("Disabled HTM\n %lx\n", mfmsr());
}


static int handler(struct module *module, int e, void *arg) {
        switch (e) {

        case MOD_LOAD:
		printf("Hello world. Modules loaded\n");
		htm_enable();
                break;

        case MOD_UNLOAD:
		printf("By world. Module unload\n");
		htm_disable();
                return 0;
        default:
                e = EOPNOTSUPP;
                break;
        }

        return(e);

}


static moduledata_t hello_data = {

    "hello_freebsd",  

     handler, 

     NULL

};

DECLARE_MODULE(hello_freebsd, hello_data, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
