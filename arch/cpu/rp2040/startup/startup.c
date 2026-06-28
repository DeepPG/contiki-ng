#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "pico/runtime.h"








extern uint32_t __StackLimit;
extern uint32_t _sdata;
extern uint32_t _sidata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;



void defaultHandler();
void resetHandler();

void nmiHandler         () __attribute__((weak, alias("defaultHandler")));
void hardFaultHandler   () __attribute__((weak, alias("defaultHandler")));
void svCallHandler      () __attribute__((weak, alias("defaultHandler")));
void pendSvHandler      () __attribute__((weak, alias("defaultHandler")));
void sysTickHandler     () __attribute__((weak, alias("defaultHandler")));

void timerIrq0          () __attribute__((weak, alias("defaultHandler")));
void timerIrq1          () __attribute__((weak, alias("defaultHandler")));
void timerIrq2          () __attribute__((weak, alias("defaultHandler")));
void timerIrq3          () __attribute__((weak, alias("defaultHandler")));
void pwmIrqWrap         () __attribute__((weak, alias("defaultHandler")));
void usbctrlIrq         () __attribute__((weak, alias("defaultHandler")));
void xipIrq             () __attribute__((weak, alias("defaultHandler")));
void pio0Irq0           () __attribute__((weak, alias("defaultHandler")));
void pio0Irq1           () __attribute__((weak, alias("defaultHandler")));
void pio1Irq0           () __attribute__((weak, alias("defaultHandler")));
void pio1Irq1           () __attribute__((weak, alias("defaultHandler")));
void dmaIrq0            () __attribute__((weak, alias("defaultHandler")));
void dmaIrq1            () __attribute__((weak, alias("defaultHandler")));
void ioIrqBank0         () __attribute__((weak, alias("defaultHandler")));
void ioIrqQspi          () __attribute__((weak, alias("defaultHandler")));
void sioIrqProc0        () __attribute__((weak, alias("defaultHandler")));
void sioIrqProc1        () __attribute__((weak, alias("defaultHandler")));
void clocksIrq          () __attribute__((weak, alias("defaultHandler")));
void spi0Irq            () __attribute__((weak, alias("defaultHandler")));
void spi1Irq            () __attribute__((weak, alias("defaultHandler")));
void uart0Irq           () __attribute__((weak, alias("defaultHandler")));
void uart1Irq           () __attribute__((weak, alias("defaultHandler")));
void adcIrqFifo         () __attribute__((weak, alias("defaultHandler")));
void i2c0Irq            () __attribute__((weak, alias("defaultHandler")));
void i2c1Irq            () __attribute__((weak, alias("defaultHandler")));
void rtcIrq             () __attribute__((weak, alias("defaultHandler")));

extern int main(void);

uint32_t __vectors[] __attribute__((section(".vectors"))) = 
{
    (uint32_t)&__StackLimit,
    (uint32_t)&resetHandler,
    (uint32_t)&nmiHandler,
    (uint32_t)&hardFaultHandler,
    (uint32_t)0,
    (uint32_t)0,
    (uint32_t)0,
    (uint32_t)0,
    (uint32_t)0,
    (uint32_t)0,
    (uint32_t)0,
    (uint32_t)&svCallHandler,
    (uint32_t)0,
    (uint32_t)0,
    (uint32_t)&pendSvHandler,
    (uint32_t)&sysTickHandler,
    (uint32_t)&timerIrq0,
    (uint32_t)&timerIrq1,
    (uint32_t)&timerIrq2,
    (uint32_t)&timerIrq3,
    (uint32_t)&pwmIrqWrap,
    (uint32_t)&usbctrlIrq,
    (uint32_t)&xipIrq,
    (uint32_t)&pio0Irq0,
    (uint32_t)&pio0Irq1,
    (uint32_t)&pio1Irq0,
    (uint32_t)&pio1Irq1,
    (uint32_t)&dmaIrq0,
    (uint32_t)&dmaIrq1,
    (uint32_t)&ioIrqBank0,
    (uint32_t)&ioIrqQspi,
    (uint32_t)&sioIrqProc0,
    (uint32_t)&sioIrqProc1,
    (uint32_t)&clocksIrq,
    (uint32_t)&spi0Irq,
    (uint32_t)&spi1Irq,
    (uint32_t)&uart0Irq,
    (uint32_t)&uart1Irq,
    (uint32_t)&adcIrqFifo,
    (uint32_t)&i2c0Irq,
    (uint32_t)&i2c1Irq,
    (uint32_t)&rtcIrq,
    (uint32_t)0,
    (uint32_t)0,
    (uint32_t)0,
    (uint32_t)0,
    (uint32_t)0,
    (uint32_t)0,
};






void resetHandler()
{


    uint32_t* flash_data_start = &_sidata;
    uint32_t* ram_data_start = &_sdata;
    

    while(ram_data_start < &_edata){
        *ram_data_start = *flash_data_start;
        ram_data_start++;
        flash_data_start++;
    }


    uint32_t* ram_bss_start = &_sbss;

    while(ram_bss_start < &_ebss){
        *ram_bss_start = 0;
        ram_bss_start++;
    }

    runtime_init();




    main();
    while(true);
}


void defaultHandler()
{
    while (true)
    {

    }
}






void __unhandled_user_irq (void) __attribute__((weak, alias("defaultHandler")));



void panic(const char *fmt, ...) __attribute__((weak, alias("defaultHandler")));



/*
 *  __assert_func live inside picolibc or newlib, it handle errors and it's weak function. Therefore we just alias it to defaultHandler for now.
*/

void __assert_func(const char *file, int line, const char *func, const char *failedexpr)  __attribute__((weak, alias("defaultHandler")));





