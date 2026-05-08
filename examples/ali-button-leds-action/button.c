
#include "contiki.h"
#include "sys/clock.h"


#define GPIO_OUTCLR  (*(volatile unsigned int *)(0x50000000UL + 0x50C))
#define GPIO_OUTSET  (*(volatile unsigned int *)(0x50000000UL + 0x508))
#define PIN6_CONF  (*(volatile unsigned int *)(0x50000000UL + 0x718UL))
#define PIN8_CONF  (*(volatile unsigned int *)(0x50000000UL + 0x720UL))
#define PIN12_CONF  (*(volatile unsigned int *)(0x50000000UL + 0x730))

#include "sys/log.h"
#include "dev/button-hal.h"
#include "dev/leds.h"
#include "sys/clock.h"




#define LOG_MODULE "app"
#define LOG_LEVEL LOG_LEVEL_INFO




PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);
PROCESS_THREAD(hello_world_process, ev, data)
{

  PROCESS_BEGIN();
  while(1) {
    PROCESS_WAIT_EVENT();
    if(ev == button_hal_press_event){
      leds_on(LEDS_YELLOW | LEDS_GREEN | LEDS_RED);
    } else if(ev == button_hal_release_event){
      leds_off(LEDS_ALL);
    }
    LOG_INFO("A button had been pressed\n");
  }

  PIN6_CONF |= (1U << 0);
  GPIO_OUTCLR |= (1U << 6);


  PIN8_CONF |= (1U << 0);
  GPIO_OUTCLR |= (1U << 8);

  PIN12_CONF |= (1U << 0);
  GPIO_OUTCLR |= (1U << 12);

  // clock_init();
  while(1){
    clock_wait(50);
    LOG_INFO("%ld\n\r", clock_seconds());
  }




  PROCESS_END();
}
