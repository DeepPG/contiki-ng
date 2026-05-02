#include "contiki.h"
#include "uart0.h"


int main(void) {
    

    rtimer_arch_init();
    clock_init();
    uart0_init();


    process_init();

    
    process_start(&etimer_process, NULL);
    autostart_start(autostart_processes);


    while(1) {
        process_run(); 
    }

    return 0;
}