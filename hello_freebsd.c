#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>


static int handler(struct module *module, int e, void *arg) {
        switch (e) {

        case MOD_LOAD:
		printf("Hello world. Modules loaded\n");
                break;

        case MOD_UNLOAD:
		printf("By world. Module unload\n");
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
