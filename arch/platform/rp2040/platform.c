#include "contiki.h"
#include "uart0.h"
#include "pico/multicore.h"


#include "sys/log.h"

#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO 







int main(void) {

    
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