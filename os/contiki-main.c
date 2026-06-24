#include "platform.h"
#include "contiki.h"


int main(void) {

    
    
    platform_init_stage_one();


    platform_init_stage_two();



    platform_init_stage_three();




    while(1) {

        process_run(); 
    }

    return 0;
}