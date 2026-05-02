#include "stm32f411xe.h"
#include "core_cm4.h"


#include <contiki.h>


void rtimer_arch_init(void){


    RCC->APB1ENR |= (1U << 1);

    TIM3->CR1 &= ~(1U << 4);

    TIM3->CNT = 0;
    TIM3->PSC = 1599;
    TIM3->ARR = 62500;


    TIM3->DIER |= (1U << 0);

    NVIC_EnableIRQ(TIM3_IRQn);


    TIM3->CR1 |= (1U << 0);

}

rtimer_clock_t rtimer_arch_now()
{
    return TIM2->CNT;
}


void TIM3_IRQHandler(void) {
    if (TIM3->SR & (1U << 0)) {
        TIM3->SR &= ~(1U << 0);

        
    }
}


