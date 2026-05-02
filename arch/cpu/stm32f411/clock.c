#include "stm32f411xe.h"
#include "core_cm4.h"
#include "contiki.h"


static volatile uint32_t ticks;


#define RTC_CONFIG_FREQUENCY 32768UL

#ifndef PREPDIV_A
#define PREPDIV_A 127UL
#endif

#ifndef PREPDIV_S
#define PREPDIV_S 1UL
#endif

#define TICKS (RTC_CONFIG_FREQUENCY / ((PREPDIV_A + 1) * (PREPDIV_S + 1))) // By default 128 ticks per second.



void clock_update(void);




void rtc_wute_init(void){

	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	RTC->CR &= ~(1U << 10);

	while(!(RTC->ISR & (1U << 2))){}


	RTC->CR &= ~(7U << 0);
	RTC->CR |= (1U << 2);

	RTC->WUTR = 0;

	RTC->CR |= (1U << 14);
	RTC->CR |= (1U << 10);




	EXTI->IMR |= (1U << 22);
	EXTI->RTSR |= (1U << 22);

	NVIC_EnableIRQ(RTC_WKUP_IRQn);


	RTC->WPR = 0xFF;


}























void rtc_init(void){


	RCC->APB1ENR |= (1U << 28);
	PWR->CR |= (1U << 8);

	RCC->BDCR |= (1 << 16);
	RCC->BDCR &= ~(1 << 16);


	RCC->BDCR |= (1U << 0);
	while(!(RCC->BDCR & (1U << 1))){}




	RCC->BDCR |= (1U << 8);
	RCC->BDCR &= ~(1U << 9);
	RCC->BDCR |= (1U << 15);



	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	RTC->ISR |= (1U << 7);
	while(!(RTC->ISR & (1U << 6))){}

	RTC->PRER = (PREPDIV_A << 16) | (PREPDIV_S << 0);


	RTC->ISR &= ~(1U << 7);



	RTC->WPR = 0xFF;



}








#ifndef RTC_ISR_WUTF
#define  RTC_ISR_WUTF (1U << 10)
#endif

#define EXTI_22 (1U << 22)


void RTC_WKUP_IRQHandler(void){
    if (RTC->ISR & RTC_ISR_WUTF) {  
        ticks++;
        RTC->ISR &= ~(RTC_ISR_WUTF);
        EXTI->PR |= EXTI_22;

		clock_update();
    }

}





void
clock_init(void)
{
    rtc_init();
    rtc_wute_init();

}



clock_time_t clock_time(void)
{
  return (clock_time_t)(ticks & 0xFFFFFFFF);
}

void clock_update(void)
{
  ticks++;
  if(etimer_pending()) {
    etimer_request_poll();
  }
}

unsigned long
clock_seconds(void)
{
  return (unsigned long)ticks / TICKS;
}



void
clock_wait(clock_time_t i)
{
  clock_time_t start;
  start = clock_time();
  while(clock_time() - start < (clock_time_t)i) {
    __WFE();
  }
}


void
clock_delay_usec(uint16_t dt)
{
  clock_time_t start;
  start = clock_time();
  while(clock_time() - start < (uint16_t)dt*128/1000) {
    __NOP();
  }
}



void
clock_delay(unsigned int i)
{
  clock_delay_usec(i);
}


