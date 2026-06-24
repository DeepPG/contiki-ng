#include "contiki.h"
#include "sys/log.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "project-conf.h"

#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO 




extern void core1_entry(void);





PROCESS(my_app_process, "My Application Process"); 
AUTOSTART_PROCESSES(&my_app_process);




static struct etimer tt;

PROCESS_THREAD(my_app_process, ev, data)
{
    PROCESS_BEGIN();  

    multicore_launch_core1(core1_entry);




    etimer_set(&tt, 1);

    while(1) {


 
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&tt));


        LOG_INFO("Test \n\r");

        etimer_reset(&tt);


    }
  
    PROCESS_END();
}  
