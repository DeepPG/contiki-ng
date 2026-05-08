#include "contiki.h"
#include "net/ipv6/simple-udp.h"
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "sys/log.h"


#define LOG_MODULE "Rpl"
#define LOG_LEVEL LOG_LEVEL_INFO


static struct simple_udp_connection udp_conn;








PROCESS(rpl_root, "The root of rpl network in mesh");
AUTOSTART_PROCESSES(&rpl_root);


static void rx_callback(struct simple_udp_connection *c,
            const uip_ip6addr_t *sender_addr,
            uint16_t sender_port,
            const uip_ip6addr_t *receiver_addr,
            uint16_t receiver_port,
            const uint8_t *data,
            uint16_t datalen)
{
  LOG_INFO_6ADDR(sender_addr);
  LOG_INFO("\n");

}


PROCESS_THREAD(rpl_root, ev, data)
{
  PROCESS_BEGIN();

  LOG_INFO("Process started\n");

  simple_udp_register(&udp_conn, 1234, NULL, 1234, rx_callback);

  NETSTACK_ROUTING.root_start();

  LOG_INFO("Root node has initialized\n");

  PROCESS_END();
}