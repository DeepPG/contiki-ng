
#include "contiki.h"
#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "hardware/sync.h"




static volatile uint32_t ticks;
void clock_update(void);

#define TICKS 10000




static bool clock_irq(struct repeating_timer *t)
{
    clock_update();
    return 1;
}






void
clock_init(void)
{

  // clock_configure(
  //       clk_sys,
  //       CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
  //       CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_XOSC_CLKSRC,
  //       12 * MHZ,
  //       10 * MHZ 
  //   );

    // pll_deinit(pll_sys); // it crash I don't know why
    // pll_deinit(pll_usb);

    // clock_stop(clk_adc);
    // clock_stop(clk_usb);
    // clock_stop(clk_rtc);

    // set_sys_clock_hz(62500 ,true); // same thing here 
    // set_sys_clock_48mhz();
    static struct repeating_timer timer;
    add_repeating_timer_ms(-1000, clock_irq, NULL, &timer); // 10khz
}




clock_time_t
clock_time(void)
{
  return (clock_time_t)(ticks & 0xFFFFFFFF);
}



void
clock_update(void)
{
  ticks++;
  if(etimer_pending()) {
    etimer_request_poll();
  }
}



unsigned long
clock_seconds(void)
{
  return (unsigned long)ticks / TICKS;
}




void
clock_wait(clock_time_t i)
{
  clock_time_t start;
  start = clock_time();
  while(clock_time() - start < (clock_time_t)i) {
    __wfe();
  }
}



void
clock_delay_usec(uint16_t dt)
{
  busy_wait_us_32(dt);
}



void
clock_delay(unsigned int i)
{
  clock_delay_usec(i);
}


