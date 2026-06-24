#include "hardware/uart.h"
#include "pico/stdlib.h"


#define UART_ID uart0

#define BAUD_RATE 115200
 
#define UART_TX_PIN 0
#define UART_RX_PIN 1



void uart0_writeb(unsigned char c){
    uart_putc(UART_ID, c);
}


// int __io_putchar(int ch){
// 	uart0_writeb(ch);
// 	return ch;
// }

void uart0_init(void){


    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);


}