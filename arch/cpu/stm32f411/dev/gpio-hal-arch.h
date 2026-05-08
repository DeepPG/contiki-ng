#ifndef STM32_GPIO__
#define STM32_GPIO__

#include <inttypes.h>

typedef uint8_t gpio_hal_port_t;
typedef uint8_t gpio_hal_pin_t;
typedef uint64_t gpio_hal_pin_mask_t;



void gpio_hal_arch_port_pin_set_input(gpio_hal_port_t port, gpio_hal_pin_t pin);
void gpio_hal_arch_port_pin_set_output(gpio_hal_port_t port, gpio_hal_pin_t pin);
void gpio_hal_arch_port_set_pin(gpio_hal_port_t port, gpio_hal_pin_t pin);
void gpio_hal_arch_port_clear_pin(gpio_hal_port_t port, gpio_hal_pin_t pin);
uint8_t gpio_hal_arch_port_read_pin(gpio_hal_port_t port, gpio_hal_pin_t pin);
void gpio_hal_arch_port_write_pin(gpio_hal_port_t port, gpio_hal_pin_t pin, uint8_t value);
gpio_hal_pin_mask_t gpio_hal_arch_port_read_pins(gpio_hal_port_t port, gpio_hal_pin_mask_t pins);
void gpio_hal_arch_port_set_pins(gpio_hal_port_t port, gpio_hal_pin_mask_t pins);
void gpio_hal_arch_port_clear_pins(gpio_hal_port_t port, gpio_hal_pin_mask_t pins);
void gpio_hal_arch_port_write_pins(gpio_hal_port_t port, gpio_hal_pin_mask_t pins, gpio_hal_pin_mask_t value);


#endif