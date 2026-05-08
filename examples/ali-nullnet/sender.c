#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"

#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO


PROCESS(nullnet_sender, "send data using nullnet");
AUTOSTART_PROCESSES(&nullnet_sender);



PROCESS_THREAD(nullnet_sender, ev, data){

    static struct etimer time;

    static linkaddr_t mac_addr = {{02, 00, 00, 00, 00, 00, 00, 00}};
    
    

    PROCESS_BEGIN();





    etimer_set(&time, CLOCK_SECOND * 5);

    while(1){
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&time));


        NETSTACK_NETWORK.output(&mac_addr);

        etimer_reset(&time);

    }



    PROCESS_END();



}