#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/stack.h>
#include <sys/sbuf.h>
#include <sys/kdb.h>

void dump(void);
void dump2(void);

void dump(){
	kdb_backtrace();
}


void dump2(){
        struct stack st;
	char buf[32];
	struct sbuf sb;
        sbuf_new(&sb, buf, sizeof(buf), SBUF_FIXEDLEN);


        stack_zero(&st);
        stack_save(&st);
        printf("stack backtrace:\n");
        stack_sbuf_print_ddb(&sb, &st);

        sbuf_finish(&sb);
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


static moduledata_t stack_data = {

    "stack",  

     handler, 

     NULL

};

DECLARE_MODULE(stack, stack_data, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
