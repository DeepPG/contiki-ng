#include "contiki.h"
#include "dev/leds.h"
#include "sys/log.h"


#define LOG_MODULE "promicro"
#define LOG_LEVEL LOG_LEVEL_INFO

PROCESS(led_test_process, "LED Test");
AUTOSTART_PROCESSES(&led_test_process);

PROCESS_THREAD(led_test_process, ev, data)
{
PROCESS_BEGIN();

    static struct etimer timer;

    etimer_set(&timer, CLOCK_SECOND*1);

    while(1){
        leds_on(LEDS_ALL);


        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));



        leds_off(LEDS_ALL);
        etimer_reset(&timer);

        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));



        LOG_INFO("Test Test Test Etsr\n");

        etimer_reset(&timer);
    }



PROCESS_END();
}