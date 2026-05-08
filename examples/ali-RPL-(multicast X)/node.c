#include "contiki.h"
#include <net/ipv6/simple-udp.h>
#include <netstack.h>
#include "sys/log.h"
#include "sys/etimer.h"
#include "net/routing/routing.h"

#define LOG_MODULE "Node"
#define LOG_LEVEL LOG_LEVEL_INFO






PROCESS(simple_node, "simple node udp that send to root in rpl");
AUTOSTART_PROCESSES(&simple_node);


static void rx_callback(struct simple_udp_connection *c,
            const uip_ip6addr_t *sender_addr,
            uint16_t sender_port,
            const uip_ip6addr_t *receiver_addr,
            uint16_t receiver_port,
            const uint8_t *data,
            uint16_t datalen)
{
    LOG_INFO("I got a message\n");

}




PROCESS_THREAD(simple_node, ev, data){

    
    
    static struct simple_udp_connection udp_conn;
    static struct etimer time;
    uip_ip6addr_t root;


    PROCESS_BEGIN();


    simple_udp_register(&udp_conn, 1234, NULL, 1234, rx_callback);

    LOG_INFO("Trying to connect\n");


    etimer_set(&time, CLOCK_SECOND * 10);
    while(1) {

        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&time));

        if(NETSTACK_ROUTING.node_is_reachable() &&
            NETSTACK_ROUTING.get_root_ipaddr(&root)) {

            // simple_udp_sendto(&udp_conn, "Hello", 5, &root);
        }

        etimer_reset(&time);
    }


    PROCESS_END();



}