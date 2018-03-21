#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/kdb.h>

void dump(void);

void dump(){
	kdb_backtrace();
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


static moduledata_t stack_data = {

    "stack",  

     handler, 

     NULL

};

DECLARE_MODULE(stack, stack_data, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
