#include "contiki.h"
#include "uart0.h"
#include "pico/multicore.h"




extern void core1_entry(void);





void platform_init_stage_one(void)
{
    clock_init();

}









void platform_init_stage_two(void)
{

    uart0_init();
    multicore_launch_core1(core1_entry);

}






void platform_init_stage_three(void)
{
    process_init();


    process_start(&etimer_process, NULL);
    autostart_start(autostart_processes);

    


}