#include <contiki.h>
#include "sys/log.h"
#include "net/nullnet/nullnet.h"
#include "net/netstack.h"


#define LOG_MODULE "receiver"
#define LOG_LEVEL LOG_LEVEL_INFO


PROCESS(receiver_nullnet, "receiver");
AUTOSTART_PROCESSES(&receiver_nullnet);

void input_callback(const void *data, uint16_t len,
                           const linkaddr_t *src,
                           const linkaddr_t *dest)
{
    LOG_INFO("received");
    LOG_INFO("\n");
}


PROCESS_THREAD(receiver_nullnet, ev, data){


    PROCESS_BEGIN();

    nullnet_set_input_callback(input_callback);

    PROCESS_END();




}