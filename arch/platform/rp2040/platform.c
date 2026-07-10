#include "contiki.h"
#include "uart0.h"
#include "pico/multicore.h"
#include "pico.h"
#include "platform.h"

extern void core1_entry(void);





void platform_init_stage_one(void)
{
    clock_init();

}









void platform_init_stage_two(void)
{

    uart0_init();

}





void platform_init_stage_three(void)
{

    process_init();


    process_start(&etimer_process, NULL);
    autostart_start(autostart_processes_core0);

    multicore_launch_core1(core1_entry);



}





volatile void core1_entry(void){
    process_init();
    autostart_start(autostart_processes_core1);
    


    while(1) {
        process_run(); 
    }

}


int rp2040_get_core_id(void) {
    return (int)get_core_num();
}