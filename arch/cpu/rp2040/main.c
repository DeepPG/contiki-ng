// #include <stdio.h>
// #include "pico/stdlib.h"
// // #include "hardware/clocks.h"
// #include "hardware/uart.h"
// #include "contiki.h"
// #include "uart0.h"





// #include "sys/log.h"



// #define LOG_MODULE "App"
// #define LOG_LEVEL LOG_LEVEL_INFO






// int main() {

//     clock_init();

//     uart0_init();

//     while(1){
//         LOG_INFO("Hello, world\n\r");

//     }

//     return 0;
// }










// // #include <stdio.h>
// // #include "hardware/rtc.h"
// // #include "pico/stdlib.h"
// // #include "pico/util/datetime.h"
// // #include "hardware/uart.h"







// // #define UART_ID uart0
// // #define BAUD_RATE 115200

// // // // We are using pins 0 and 1, but see the GPIO function select table in the
// // // // datasheet for information on which other pins can be used.
// // #define UART_TX_PIN 0
// // #define UART_RX_PIN 1


// // static volatile bool fired = false;

// // ISR: Keep it incredibly short
// // static bool alarm_callback(struct repeating_timer *t) {
// //     uart_puts(UART_ID, "System Booting...\n");
// //     fired = true;
// //     return 1;
// // }

// // int main() {
// //     uart_init(UART_ID, BAUD_RATE);
// //     gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
// //     gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

// //     uart_puts(UART_ID, "System Booting...\n");

// //     struct repeating_timer timer;
    
// //     // Negative delay (-1000) means fire precisely every 1000ms 
// //     // regardless of how long the callback execution takes
// //     add_repeating_timer_ms(-1000, alarm_callback, NULL, &timer);

// //     while (1) {
// //         if (fired) {
// //             uart_puts(UART_ID, "RTC Alarm Fired!\n");
// //             fired = false; // Acknowledge the flag
// //         }
        
// //         // Sleep until the RTC (or any other) interrupt wakes the CPU
// //     }

// // }
































// // #include <stdint.h>




// // #include "pico/stdlib.h"
// // #include "hardware/gpio.h"





// // int main(void) {

// //     gpio_init(3);



// //     gpio_set_dir(3, GPIO_OUT);

// //     while(1) {
// //         for(volatile int x = 0; x < 99999; x++){}

// //         gpio_put(3, 1);

// //         for(volatile int x = 0; x < 99999; x++){}
        

// //         gpio_put(3, 0);
// //     }
    
// //     return 0;
// // }










// /*
// Notes:
// got error for watchdog_reboot multiple definition confilcting with pico-sdk and contiki-ng 

// */