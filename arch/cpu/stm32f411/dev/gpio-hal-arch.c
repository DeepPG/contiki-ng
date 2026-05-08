#include "stm32f411xe.h"

typedef uint8_t gpio_hal_port_t;
typedef uint8_t gpio_hal_pin_t;
typedef uint32_t gpio_hal_pin_mask_t;

void gpio_hal_arch_port_pin_set_input(uint8_t port, uint8_t pin)
{
	pin = pin*2;
	switch (port){
		case 0:
		GPIOA->MODER |= (1U<<pin);
		GPIOA->MODER &= ~(1U<<(pin + 1));
		break;

		case 1:
		GPIOA->MODER |= (1U<<pin);
		GPIOA->MODER &= ~(1U<<(pin + 1));
		break;

		case 2:
		GPIOA->MODER |= (1U<<pin);
		GPIOA->MODER &= ~(1U<<(pin + 1));
		break;

		case 3:
		GPIOA->MODER |= (1U<<pin);
		GPIOA->MODER &= ~(1U<<(pin + 1));
		break;

		case 4:
		GPIOA->MODER |= (1U<<pin);
		GPIOA->MODER &= ~(1U<<(pin + 1));
		break;
	}
} 


void gpio_hal_arch_port_pin_set_output(uint8_t port, uint8_t pin){
	pin = pin*2;
	switch (port){
		case 0:
		GPIOA->MODER &= ~(1U<<pin);
		GPIOA->MODER &= ~(1U<<(pin + 1));
		break;

		case 1:
		GPIOA->MODER &= ~(1U<<pin);
		GPIOA->MODER &= ~(1U<<(pin + 1));
		break;

		case 2:
		GPIOA->MODER &= ~(1U<<pin);
		GPIOA->MODER &= ~(1U<<(pin + 1));
		break;

		case 3:
		GPIOA->MODER &= ~(1U<<pin);
		GPIOA->MODER &= ~(1U<<(pin + 1));
		break;

		case 4:
		GPIOA->MODER &= ~(1U<<pin);
		GPIOA->MODER &= ~(1U<<(pin + 1));
		break;
	}
}

void gpio_hal_arch_port_set_pin(gpio_hal_port_t port, gpio_hal_pin_t pin){

	switch (port){
		case 0:
		GPIOA->ODR |= (1U<<pin);
		break;

		case 1:
		GPIOA->ODR |= (1U<<pin);
		break;

		case 2:
		GPIOA->ODR |= (1U<<pin);
		break;

		case 3:
		GPIOA->ODR |= (1U<<pin);
		break;

		case 4:
		GPIOA->ODR |= (1U<<pin);
		break;
	}
}



void gpio_hal_arch_port_clear_pin(gpio_hal_port_t port, gpio_hal_pin_mask_t pin){

		switch (port){
		case 0:
		GPIOA->ODR &= ~(1U<<pin);
		break;

		case 1:
		GPIOA->ODR &= ~(1U<<pin);
		break;

		case 2:
		GPIOA->ODR &= ~(1U<<pin);
		break;

		case 3:
		GPIOA->ODR &= ~(1U<<pin);
		break;

		case 4:
		GPIOA->ODR &= ~(1U<<pin);
		break;
	}
	
}



uint8_t gpio_hal_arch_port_read_pin(gpio_hal_port_t port, gpio_hal_pin_t pin){
	switch (port){
		case 0:
		return !!(GPIOA->ODR & (1U<<pin));
		break;

		case 1:
		return !!(GPIOB->ODR & (1U<<pin));
		break;

		case 2:
		return !!(GPIOC->ODR & (1U<<pin));
		break;

		case 3:
		return !!(GPIOD->ODR & (1U<<pin));
		break;

		case 4:
		return !!(GPIOE->ODR & (1U<<pin));
		break;
		default:
		return 0;
	}
}



void gpio_hal_arch_port_write_pin(gpio_hal_port_t port, gpio_hal_pin_t pin, uint8_t value){
	switch (port){
		case 0:
		GPIOA->ODR = (GPIOA->ODR & ~(1U << pin)) | ((!!value) << pin);
		break;

		case 1:
		GPIOB->ODR &= (GPIOA->ODR & ~(1U << pin)) | ((!!value) << pin);
		break;

		case 2:
		GPIOC->ODR &= (GPIOA->ODR & ~(1U << pin)) | ((!!value) << pin);
		break;

		case 3:
		GPIOD->ODR &= (GPIOA->ODR & ~(1U << pin)) | ((!!value) << pin);
		break;

		case 4:
		GPIOE->ODR &= (GPIOA->ODR & ~(1U << pin)) | ((!!value) << pin);
		break;
	}
}






gpio_hal_pin_mask_t gpio_hal_arch_port_read_pins(gpio_hal_port_t port, gpio_hal_pin_mask_t pins){
	switch (port){
		case 0:
		return (gpio_hal_pin_mask_t)(GPIOA->ODR & pins);
		break;

		case 1:
		return (gpio_hal_pin_mask_t)(GPIOA->ODR & pins);
		break;

		case 2:
		return (gpio_hal_pin_mask_t)(GPIOA->ODR & pins);
		break;

		case 3:
		return (gpio_hal_pin_mask_t)(GPIOA->ODR & pins);
		break;

		case 4:
		return (gpio_hal_pin_mask_t)(GPIOA->ODR & pins);
		break;
		default:
		return 0;
	}

}








void gpio_hal_arch_port_set_pins(gpio_hal_port_t port, gpio_hal_pin_mask_t pins){

	switch (port){
		case 0:
		GPIOA->ODR |= (pins << 0);
		break;

		case 1:
		GPIOA->ODR |= (pins << 0);
		break;

		case 2:
		GPIOA->ODR |= (pins << 0);
		break;

		case 3:
		GPIOA->ODR |= (pins << 0);
		break;

		case 4:
		GPIOA->ODR |= (pins << 0);
		break;
	}

}



void gpio_hal_arch_port_clear_pins(gpio_hal_port_t port, gpio_hal_pin_mask_t pins){

	switch (port){
		case 0:
 		GPIOA->ODR &= ~(pins << 0);

		GPIOA->ODR &= ~(pins << 0);
		break;

		case 1:
		GPIOB->ODR &= ~(pins << 0);
		break;

		case 2:
		GPIOC->ODR &= ~(pins << 0);
		break;

		case 3:
		GPIOD->ODR &= ~(pins << 0);
		break;

		case 4:
		GPIOE->ODR &= ~(pins << 0);
		break;
	}

}






void gpio_hal_arch_port_write_pins(gpio_hal_port_t port, gpio_hal_pin_mask_t pins, gpio_hal_pin_mask_t value){
	switch (port){
		case 0:
		GPIOA->ODR = (GPIOA->ODR & ~pins) | (value & pins);
		break;

		case 1:
		GPIOB->ODR &= (GPIOA->ODR & ~pins) | (value & pins);
		break;

		case 2:
		GPIOC->ODR &= (GPIOA->ODR & ~pins) | (value & pins);
		break;

		case 3:
		GPIOD->ODR &= (GPIOA->ODR & ~pins) | (value & pins);
		break;

		case 4:
		GPIOE->ODR &= (GPIOA->ODR & ~pins) | (value & pins);
		break;
	}
}