#include "stm32f411xe.h"
#include "core_cm4.h"


#include <contiki.h>


void rtimer_arch_init(void){


    RCC->APB1ENR |= (1U << 3);


    TIM5->CR1 &= ~(1U << 4);



    TIM5->CNT = 0;
    TIM5->PSC = 256; // Trying to set it to 65000 Hz but it's not working, it's 16 Mhz by default. 
    TIM5->ARR = 5;


    TIM5->DIER |= (1U << 0);
    NVIC_EnableIRQ(TIM5_IRQn);


    TIM5->CR1 |= (1U << 0);

}

rtimer_clock_t rtimer_arch_now()
{
    return TIM5->CNT;
}

void rtimer_arch_schedule(rtimer_clock_t t)
{
    TIM5->CNT = t;
}


void TIM5_IRQHandler(void) {
    if (TIM5->SR & (1U << 0)) {
        TIM5->SR &= ~(1U << 0);
        rtimer_run_next();
        
    }
}


