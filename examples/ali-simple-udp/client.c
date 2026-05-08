#include "dev/gpio-hal.h"
#include "contiki.h"
#include "dev/leds.h"
#include "sys/log.h"
#include "stm32f411xe.h"


#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO 

PROCESS(my_app_process, "My Application Process");
AUTOSTART_PROCESSES(&my_app_process);

static struct etimer tt;

PROCESS_THREAD(my_app_process, ev, data)
{
    PROCESS_BEGIN();  

    etimer_set(&tt, CLOCK_SECOND);
    gpio_hal_arch_set_pin(0,5);
    gpio_hal_arch_port_pin_set_input(0, 5);
    gpio_hal_arch_write_pins(0, 63, 7);
    leds_single_on(LEDS_GREEN);
    // GPIOA->ODR &= ~(63U << 0);

    while(1) {


 
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&tt));

        LOG_INFO("%d", RTIMER_SECOND);

        etimer_reset(&tt);


    }
  
    PROCESS_END();
}   