#include "stm32f411xe.h"




void uart0_writeb(unsigned char c){
	while(!(USART2->SR & (1U << 7))){}
	USART2->DR =(c);
}


int __io_putchar(int ch){
	uart0_writeb(ch);
	return ch;
}

void uart0_init(void){



	RCC->AHB1ENR |= (1U << 0);
	RCC->APB1ENR |= (1U << 17);
	GPIOA->MODER &= ~(1U << 4);
	GPIOA->MODER |= (1U << 5);

	GPIOA->AFR[0] |=(1U<<8); 
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);



	USART2->BRR = ((16000000 + 115200/2)/115200);
 
	USART2->CR1 |= (1U << 13);
	USART2->CR1 |= (1U << 3);

}


























































// void uart_print_number(uint32_t num) {
//     char buffer[11];
//     int i = 0;

//     if (num == 0) {
//         uart_write('0');
//         return;
//     }
//     while (num > 0) {
//         buffer[i++] = (num % 10) + '0';
//         num /= 10;
//     } 

//     while (i > 0) {
//         uart_write(buffer[--i]);
//     }
    
//     uart_write('\r');
//     uart_write('\n');
// }