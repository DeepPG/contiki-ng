#include "contiki.h"
#include "sys/log.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "project-conf.h"


#define LOG_MODULE "CORE0"
#define LOG_LEVEL LOG_LEVEL_INFO 





PROCESS(my_app_process, "My Application Process"); 
AUTOSTART_PROCESSES(core0 ,&my_app_process);




static struct etimer tt;

PROCESS_THREAD(my_app_process, ev, data)
{
    PROCESS_BEGIN();


    etimer_set(&tt, (1001));

    while(1) {

 
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&tt));

        LOG_INFO("I'm CORE %d and PROCESS 1\n\r", get_core_num());


        etimer_reset(&tt);


    }
  
    PROCESS_END();
}  
