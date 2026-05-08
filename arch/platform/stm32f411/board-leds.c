#include "contiki.h"
#include "dev/leds.h"
#include "dev/gpio-hal.h"

#include <stdbool.h>
/*---------------------------------------------------------------------------*/
const leds_t leds_arch_leds[] = {
  {
    .port = 0,
    .pin = 5,
    .negative_logic = false
  },
};