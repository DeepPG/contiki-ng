#include "contiki.h"
#include "sys/etimer.h"
#include "sys/ctimer.h"
#include "sys/log.h"
// #define CLOCK_SECOND  1000
#define LOG_MODULE "YIELD"
#define LOG_LEVEL LOG_LEVEL_INFO


int i = 0;

PROCESS(yield_example, "First thread");
PROCESS(yield_example2, "Second thread");

AUTOSTART_PROCESSES(&yield_example, &yield_example2);



PROCESS_THREAD(yield_example, ev, data){
  PROCESS_BEGIN();

  while(1) {
    int limit = i + 1000;
    for(; i <= limit; i++) {
      LOG_INFO("%d\n", i);
    }
    process_post(&yield_example2, PROCESS_EVENT_NONE, NULL);
    PROCESS_WAIT_EVENT();
  }

  PROCESS_END();
}

PROCESS_THREAD(yield_example2, ev, data){

  PROCESS_BEGIN();

  while(1) {
    int limit = i + 1000;
    for(; i <= limit; i++) {
      LOG_INFO("%d\n", i);
    }
    process_post(&yield_example, PROCESS_EVENT_NONE, NULL);
    PROCESS_WAIT_EVENT();
  }

  PROCESS_END();
}